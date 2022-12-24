#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

char query[256];

void mysql_err(MYSQL *con) {
	printf("ERROR %d: %s\n", mysql_errno(con), mysql_error(con));
	mysql_close(con);
	exit(0);
}

void add_transact(MYSQL *con) {
	unsigned short amount;
	int price;
	printf("So luong: ");
	scanf("%hu", &amount);
	printf("Don gia: ");
	scanf("%d", &price);

	sprintf(query, "insert into transactions values(NULL, %hu, %i)", amount, price);
	if (mysql_query(con, query)) mysql_err(con);
	printf("OK\n");
}

void query_transact(MYSQL *con) {
	int id;
	MYSQL_RES *res;
	MYSQL_FIELD *col;
	MYSQL_ROW row;

	printf("Nhap so hieu: ");
	scanf("%d", &id);
	sprintf(query, "select * from transactions where ID=%d", id);
	if (mysql_query(con, query)) mysql_err(con);
	res = mysql_store_result(con);

	if ((row = mysql_fetch_row(res)) != NULL) {
		col = mysql_fetch_field(res);
		printf("%-4s", col->name);
		col = mysql_fetch_field(res);
		printf("%-10s", col->name);
		col = mysql_fetch_field(res);
		printf("%-8s\n", col->name);

		printf("%-4s%-10s%-8s\n", row[0], row[1], row[2]);
	} else {
		printf("Khong co truy van nao\n");
	}
	mysql_free_result(res);
}

void sum(MYSQL *con) {
	MYSQL_RES *res;
	MYSQL_ROW row;

	strcpy(query, "select sum(so_luong*don_gia) as tong from transactions");
	if (mysql_query(con, query)) mysql_err(con);
	res = mysql_store_result(con);
	row = mysql_fetch_row(res);

	printf("Tong: %s d\n", row[0]);
	mysql_free_result(res);
}

int main() {
	MYSQL conn;
	int option;

	if (mysql_init(&conn) == NULL) mysql_error(&conn);
	if (mysql_real_connect(&conn, "127.0.0.1", getenv("MYSQL"), getenv("PASS"), "20020722db", 3306, NULL, 0) == NULL)
		mysql_error(&conn);
	printf("Connection OK\n");
	printf("Command:\n");
	printf("1: Them giao dich\n");
	printf("2: Tim kiem giao dich\n");
	printf("3: Tinh tong tien giao dich\n");
	printf("0: Thoat\n");
	printf("Command: ");
	scanf("%d", &option);
	while (option != 0) {
		switch(option) {
			case 1:
				add_transact(&conn);
				break;
			case 2:
				query_transact(&conn);
				break;
			case 3:
				sum(&conn);
				break;
		}
		printf("Command: ");
		scanf("%d", &option);
	}
	mysql_close(&conn);
	exit(0);
}
