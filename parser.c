#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
int main(int argc,char ** argv)
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
    /*struct data{
        char * id;
        char * Value;

    };
    typedef struct data data_t;*/

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
    printf("%s \n",Value[0]);

    root=xmlLastElementChild(temp);
    first_child = root;
    for (node = first_child; node; node = node->next) {

        if(node->type==1)
        {
            id[i]=(char*)node->name;
            Value[i]=(char*)xmlNodeGetContent(node);
            //printf("%s :%s\n",id[i],Value[i]);
            i++;
        }
    }

        //printf("%s \n",Value[0]);




    return EXIT_SUCCESS;

}
