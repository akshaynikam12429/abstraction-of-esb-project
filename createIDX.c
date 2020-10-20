#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>



static char *host ="localhost";
static char *user = "akshaynikam";
static char *password = "Akshay@123";
static char *dbname ="createDB";


static char *unix_socket = NULL;
unsigned int flag =0;


int main(int argc, char **argv)
{
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

      if(mysql_query(con," CREATE INDEX UK_sender_dest_msg_type ON esb_request(sender_id,dest_id,message_type)"))

   {

             fprintf(stderr, "%s\n", mysql_error(con));
                     mysql_close(con);
                         exit(1);
      }

   
                           mysql_close(con);
                         exit(0);

}

