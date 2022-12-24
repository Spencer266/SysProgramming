#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void error(MYSQL *con) {
	printf("ERROR %d: %s\n", mysql_errno(con), mysql_error(con));
	mysql_close(con);
	exit(1);
}

int main() {
	MYSQL conn;
	MYSQL_RES *result;
	MYSQL_FIELD *columns;
	MYSQL_ROW rows;
	char query[256];
	int num_field;

	if (mysql_init(&conn)) {
		printf("Initialized\n");
	} else {
		error(&conn);
	}
	if (mysql_real_connect(&conn, "127.0.0.1", getenv("MYSQL"), getenv("PASS"), "20020722db", 3306, NULL, 0)) {
		printf("Connected\n");
	}
	else {
		error(&conn);
	}

	sprintf(query, "select * from STUDENTS");
	printf("%s\n", query);
	if (mysql_query(&conn, query) < 0)
		error(&conn);

	result = mysql_store_result(&conn);
	num_field = mysql_num_fields(result);

	while((columns = mysql_fetch_field(result)) != NULL) {
		printf("%s\t", columns->name);
	}
	printf("\n");

	while((rows = mysql_fetch_row(result)) != NULL) {
		for (int i = 0; i < num_field; i++)
			printf("%-8s", rows[i]);
		printf("\n");
	}
	mysql_close(&conn);
	exit(0);
}
