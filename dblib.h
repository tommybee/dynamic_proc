/* --------------------------------------------------------------------------------
파일 이름 : dblib.h
개발 일자 : 2002-10-28
작성자 : 류명환
-------------------------------------------------------------------------------- */



#ifndef __DB_LIB_H__
#define __DB_LIB_H__


#ifdef __cplusplus
extern "C"
{
#endif

/*
 * dblib.h
 * dblib.pc에서 사용하는 매크로 등을 넣어둔 파일
 */

#define FALSE           0
#define TRUE            !FALSE

#define FAILURE         EXIT_FAILURE
#define SUCCESS         EXIT_SUCCESS
#define FETCH_DONE      100

#define COMMIT          0
#define ROLLBACK        1

#define MAX_SQL_LEN     2048 * 10

#define MAX_NAME_LEN    32
#define MAX_DATA_LEN    4096

#define MAX_ROWS        65536

/*
 * ANSI SQL Datatypes
 */
#define CHAR      1
#define VARCHAR2    12
#define DATE      9
#define DECIMAL      3
#define DOUBLE      8
#define FLOAT      6
#define INTEGER      4
#define NUMBER      2
#define REAL      7
#define SHORT      5
#define SMALLINT    5



char *ora_sqlerrm (void);
int ora_sqlcode (void);
int ora_connect (const char *user, const char *pass, const char *db);
int ora_connect_tns (const char *tns_str);
int ora_disconnect (int mode);
int ora_commit (void);
int ora_rollback (void);
int ora_setstmt (char *str);
char *ora_getstmt (char *buf);
int ora_execute (int *ncols);
int ora_bind_params (int *ncols, char *params, ...);
int ora_bind_params2 (int *ncols, char *params, ...);
int ora_bind_u_params (char *params, ...);
int ora_select_open (int *ncols);
int ora_select_fetch_name (char *pdata, int pos);
int ora_select_set_column (int pos, int type, int length);
int ora_select_fetch_row (void);
int ora_select_fetch_data (char *pdata, int pos);
int ora_select_close (void);

#ifdef __cplusplus
}
#endif

#endif
