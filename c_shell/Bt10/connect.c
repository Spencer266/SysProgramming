#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[])
{
	MYSQL connection;
	if (mysql_init(&connection))
		printf("Connection handle initialized\n");
	else {
		printf("Connection handle failed\n");
		exit(1);
	}

	if (mysql_real_connect(&connection, "127.0.0.1", "root", "Viktor123@", "20020722db", 3306, NULL, 0))
		printf("Connection to MySQL OK\n");
	else {
		printf("Connection to remote MySQL failed\n");
		exit(1);
	}
	mysql_close(&connection);
	exit(0);
}
