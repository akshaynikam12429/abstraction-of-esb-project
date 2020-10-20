#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <mysql.h>
#include <stdlib.h>
#define MAX_STRING 1000


static char *host ="localhost";
static char *user = "akshaynikam";
static char *password = "Akshay@123";
static char *dbname ="createDB";


static char *unix_socket = NULL;
unsigned int flag =0;


int main(int argc, char **argv)
{
    if(argc!=2){
        fprintf(stderr,"Invalid number of arguments\n");
        return EXIT_FAILURE;
    }
    xmlDoc         *document;
    xmlNode        *root, *first_child, *node,*temp;

    //reading xml file
    document = xmlReadFile(argv[1], NULL, 0);
    if(document==NULL){
        fprintf(stderr,"Could not parse the file: %s\n",argv[1]);
        return EXIT_FAILURE;
    }

    //getting root element of xml file
    temp = xmlDocGetRootElement(document);
    root=xmlFirstElementChild(temp);
    struct envelope{
        char * messageId;
        char * messageType;
        char * sender;
        char * destination;
        char * creationDateTime;
        char * signature;
        char * referenceId;
        char * userProperties;
    };
    struct envelope envelope_t;

    char* id[8];
    char* Value[8];
    int i=0;
    first_child = root->children;
    for (node = first_child; node; node = node->next) {

        if(node->type==1)
        {
            id[i]=(char*)node->name;
            Value[i]=(char*)xmlNodeGetContent(node);
            //printf("%s :%s\n",id[i],Value[i]);
            i++;
        }
    }
    envelope_t.messageId=Value[0];
    envelope_t.messageType=Value[1];
    envelope_t.sender=Value[2];
    envelope_t.destination=Value[3];
    envelope_t.creationDateTime=Value[4];
    envelope_t.signature=Value[5];
    envelope_t.referenceId=Value[6];
    envelope_t.userProperties=Value[7];


    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, host, user, password,
                           dbname, 0, unix_socket, flag) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);

    }

    if (mysql_query(con, "DROP TABLE IF EXISTS esb_request"))
    {

        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);

    }

    if (mysql_query(con, "CREATE TABLE esb_request(id INT,sender_id VARCHAR(100),dest_id VARCHAR(100),message_type VARCHAR(100),reference_id VARCHAR(100),message_id VARCHAR(100),received_on VARCHAR(100),data_location TEXT,status VARCHAR(100),status_details TEXT)"))

    {

        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);

    }

    char  query[MAX_STRING]={0};
    snprintf(query,MAX_STRING,"INSERT INTO esb_request(message_id,message_type,sender_id,dest_id,received_on,reference_id) VALUES('%s','%s','%s','%s','%s','%s')",envelope_t.messageId,envelope_t.messageType,envelope_t.sender,envelope_t.destination,envelope_t.creationDateTime,envelope_t.referenceId);
    if (mysql_query(con,(query))) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }


    mysql_close(con);
    exit(0);
}












