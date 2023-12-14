#include <mysql/mysql.h>

int main() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
       // fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(con, "localhost", "root", "geslo123", "test", 0, NULL, 0) == NULL) {
        //fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(con);
        return 1;
    }

    if (mysql_query(con, "SELECT * FROM Ports") != 0) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(con));
        mysql_close(con);
        return 1;
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(con));
        mysql_close(con);
        return 1;
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)) != NULL) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);
    mysql_close(con);

    return 0;
}
