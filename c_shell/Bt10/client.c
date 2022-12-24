#include <stdio.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
	printf("MySQL client verison: %s\n", mysql_get_client_info());
	return 0;
}
