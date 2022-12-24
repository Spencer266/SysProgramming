#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

typedef struct student_record {
	int ID;
	char name[20];
	int score;
	char email[40];
	struct book_order {
		char name[20];
		char time[10];
	} order;
} Record;

void mysql_err(MYSQL *con) {
	printf("ERROR %d: %s\n", mysql_errno(con), mysql_error(con));
	mysql_close(con);
	exit(1);
}

void email_query(MYSQL *con) {
	MYSQL_RES *res;
	MYSQL_FIELD *column;
	MYSQL_ROW row;

	if (mysql_query(con, "select emails.ID, name as student, email from emails join student on emails.ID=student.ID")) mysql_err(con);
	res = mysql_store_result(con);

	column = mysql_fetch_field(res);
	printf("%-4s", column->name);
	column = mysql_fetch_field(res);
	printf("%-30s", column->name);
	column = mysql_fetch_field(res);
	printf("%-20s\n", column->name);

	while ((row = mysql_fetch_row(res)) != NULL) {
		printf("%-4s%-30s%-20s\n", row[0], row[1], row[2]);
	}
}

void update_grade(MYSQL *con) {
	if (mysql_query(con, "update student set grade = case when score>=90 then 'A' when score>=80 and score<90 then 'B' when score>=70 and score<80 then 'C' else 'D' end"))
		mysql_err(con);
}

int main(int argc, char *argv[]) {
	MYSQL conn;
	char query[512];
	char buf[100];
	FILE *fp = fopen("QH2002", "r");
	Record students[10];
	int i = atoi(argv[1]);

	if (mysql_init(&conn) == NULL)
		mysql_err(&conn);
	if (mysql_real_connect(&conn, "127.0.0.1", getenv("MYSQL"), getenv("PASS"), "20020722db", 3306, NULL, 0) == NULL)
		mysql_err(&conn);

	printf("Connected\n");
	strcpy(query, "create table if not exists student(ID int not null primary key auto_increment, name varchar(20) not null, score int, grade varchar(10))");
	if (mysql_query(&conn, query)) mysql_err(&conn);

	strcpy(query, "create table if not exists emails(ID int not null primary key auto_increment, email varchar(40), student_id int not null, foreign key (student_id) references student(id))");
	if (mysql_query(&conn, query)) mysql_err(&conn);

	strcpy(query, "create table if not exists book(ID int not null primary key auto_increment, name varchar(20) not null unique, time date not null, student_id int, foreign key (student_id) references student(ID))");
	if (mysql_query(&conn, query)) mysql_err(&conn);

	while (fgets(buf, 100, fp) != NULL) {
		sscanf(buf, "%[^,],%d,%[^,],%[^,],%s", students[i].name, &students[i].score, students[i].email, students[i].order.name, students[i].order.time);
		sprintf(query, "INSERT INTO student VALUES(%d, '%s', %d, NULL)\n", i+1, students[i].name, students[i].score);
		if (mysql_query(&conn, query)) mysql_err(&conn);
		sprintf(query, "INSERT INTO emails VALUES(%d, '%s', %d)\n", i+1, students[i].email, i+1);
		if (mysql_query(&conn, query)) mysql_err(&conn);
		sprintf(query, "INSERT INTO book VALUES(%d, '%s', '%s', %d)\n", i+1, students[i].order.name, students[i].order.time, i+1);
		if (mysql_query(&conn, query)) mysql_err(&conn);
		i++;
	}

	update_grade(&conn);
	email_query(&conn);

	fclose(fp);
	mysql_close(&conn);
	exit(0);
}
