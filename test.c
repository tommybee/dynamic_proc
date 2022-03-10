/* --------------------------------------------------------------------------------
파일 이름 : test.c
개발 일자 : 2002-10-28
작성자 : 류명환
-------------------------------------------------------------------------------- */

/*
 * test.c
 * dblib.c 를 사용하여 SQL 문장을 동적으로 할당한 예제
 * 모든 함수 수행에 ret 변수에 결과를 받는다.
 * ret 변수를 검사하여 함수의 실행 결과를 알 수 있다. 
 http://www.joinc.co.kr/w/Site/Database/Book/ProcPrograming/8.Dynamic_SQL
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dblib.h"

int test_select (void)
{
	int i;
	int ret;
	int ncols;
	char stmt [MAX_SQL_LEN];
	char data [MAX_DATA_LEN];
	
	strcpy (stmt, "SELECT * FROM TB_LOG_USR_LOGIN WHERE USERID = 'b_admin' AND USERIP='192.168.200.114';");
	
	//ret = ora_connect ("scott", "tiger", NULL);
	ret = ora_connect_tns("s_test/s_test@(DESCRIPTION=(ADDRESS_LIST=(ADDRESS=(PROTOCOL=TCP)(HOST=168.150.182.72)(PORT=1521)))(CONNECT_DATA=(SERVER=DEDICATED)(SERVICE_NAME=STEST)))");
	
	if(ret == SUCCESS)
	{
		printf("success!!!\n");
	}
	
	ret = ora_setstmt (stmt);
	
	ret = ora_select_open (&ncols);
	printf ("\n-------------------ncols %d------------------------------------\n", ncols);
	for (i = 1; i <= ncols; i ++)
	{
		ret = ora_select_fetch_name (data, i);
		printf ("%-10s ", data);
	}
	printf ("\n-------------------------------------------------------\n");
	
	for (i = 1; i <= ncols; i ++)
	{
		ret = ora_select_set_column (i, VARCHAR2, MAX_DATA_LEN);
	}
	
	
	while (ora_select_fetch_row () == SUCCESS)
	{
	
		if(ora_sqlcode () == FETCH_DONE) break;
		
		for (i = 1; i <= ncols; i ++)
		{
			ret = ora_select_fetch_data (data, i);
			
			printf ("%-10s", data);
		}
		printf ("\n");
	}
	
	ret = ora_disconnect (ROLLBACK);
	
	exit (EXIT_SUCCESS);
}

int test_arg_select (void)
{
	int i;
	int ret;
	int ncols;
	char stmt [MAX_SQL_LEN];
	char data [MAX_DATA_LEN];
	
	//strcpy (stmt, "SELECT * FROM TB_LOG_USR_LOGIN WHERE USERID = 'b_admin' AND USERIP='192.168.200.114';");
	strcpy (stmt, "SELECT * FROM TB_LOG_USR_LOGIN WHERE USERID = :userid AND USERIP=:userip;");
	
	//ret = ora_connect ("scott", "tiger", NULL);
	ret = ora_connect_tns("s_test/s_test@(DESCRIPTION=(ADDRESS_LIST=(ADDRESS=(PROTOCOL=TCP)(HOST=168.150.182.72)(PORT=1521)))(CONNECT_DATA=(SERVER=DEDICATED)(SERVICE_NAME=STEST)))");
	
	if(ret == SUCCESS)
	{
		printf("success!!!\n");
	}
	
	ret = ora_setstmt (stmt);
	
	ret = ora_select_open (&ncols);
	
	printf ("\n-------------------ncols %d------------------------------------\n", ncols);
	for (i = 1; i <= ncols; i ++)
	{
		ret = ora_select_fetch_name (data, i);
		printf ("%-10s ", data);
	}
	printf ("\n-------------------------------------------------------\n");
	
	for (i = 1; i <= ncols; i ++)
	{
		ret = ora_select_set_column (i, VARCHAR2, MAX_DATA_LEN);
	}
	
	
	while (ora_select_fetch_row () == SUCCESS)
	{
	
		if(ora_sqlcode () == FETCH_DONE) break;
		
		for (i = 1; i <= ncols; i ++)
		{
			ret = ora_select_fetch_data (data, i);
			
			printf ("%-10s", data);
		}
		printf ("\n");
	}
	
	ret = ora_disconnect (ROLLBACK);
	
	exit (EXIT_SUCCESS);
}

int test_arg_auto_select (void)
{
	int i;
	int ret;
	int ncols;
	char stmt [MAX_SQL_LEN];
	char data [MAX_DATA_LEN];
	
	//strcpy (stmt, "SELECT * FROM TB_LOG_USR_LOGIN WHERE USERID = 'b_admin' AND USERIP='192.168.200.114';");
	//strcpy (stmt, "SELECT * FROM TB_LOG_USR_LOGIN WHERE USERID = :userid AND USERIP=:userip;");
	strcpy (stmt, "SELECT * FROM TB_ADDR_MAP_TEMP_REF_JIBUN WHERE BJD_CD = :bjd_cd;");
	
	//ret = ora_connect ("scott", "tiger", NULL);
	ret = ora_connect_tns("s_test/s_test@(DESCRIPTION=(ADDRESS_LIST=(ADDRESS=(PROTOCOL=TCP)(HOST=168.150.182.72)(PORT=1521)))(CONNECT_DATA=(SERVER=DEDICATED)(SERVICE_NAME=STEST)))");
	
	if(ret == SUCCESS)
	{
		printf("success!!!\n");
	}
	
	ret = ora_setstmt (stmt);
	
	ret = ora_bind_params (&ncols, "%s", "2911012200");
	
	printf ("\n-------------------ncols %d------------------------------------\n", ncols);
	for (i = 1; i <= ncols; i ++)
	{
		ret = ora_select_fetch_name (data, i);
		printf ("%-10s ", data);
	}
	printf ("\n-------------------------------------------------------\n");
	
	for (i = 1; i <= ncols; i ++)
	{
		ret = ora_select_set_column (i, VARCHAR2, MAX_DATA_LEN);
	}
	
	
	while (ora_select_fetch_row () == SUCCESS)
	{
	
		if(ora_sqlcode () == FETCH_DONE) break;
		
		for (i = 1; i <= ncols; i ++)
		{
			ret = ora_select_fetch_data (data, i);
			
			printf ("%-10s", data);
		}
		printf ("\n");
	}
	
	ret = ora_disconnect (ROLLBACK);
	
	exit (EXIT_SUCCESS);
}


int test_arg_auto_insert (void)
{
	int i;
	int ret;
	int ncols;
	int idx;
	char stmt [MAX_SQL_LEN];
	char data [MAX_DATA_LEN];
	
	char sql_qry [MAX_DATA_LEN];
	
	idx = sprintf(sql_qry, "%s", "INSERT INTO TB_ADDR_MAP_TEMP_REF_JIBUN ");
	idx += sprintf(sql_qry+idx, "%s", "(                                       ");
	idx += sprintf(sql_qry+idx, "%s", "	BJD_CD,                              ");
	idx += sprintf(sql_qry+idx, "%s", "	SIDO_NM,                             ");
	idx += sprintf(sql_qry+idx, "%s", "	SIGG_NM,                             ");
	idx += sprintf(sql_qry+idx, "%s", "	EMD_NM,                              ");
	idx += sprintf(sql_qry+idx, "%s", "	RI_NM,                               ");
	idx += sprintf(sql_qry+idx, "%s", "	SAN_CK,                              ");
	idx += sprintf(sql_qry+idx, "%s", "	JIBUN_MAIN,                          ");
	idx += sprintf(sql_qry+idx, "%s", "	JIBUN_SUB,                           ");
	idx += sprintf(sql_qry+idx, "%s", "	RD_CD,                               ");
	idx += sprintf(sql_qry+idx, "%s", "	GRND_CK,                             ");
	idx += sprintf(sql_qry+idx, "%s", "	BLDNO_MAIN,                          ");
	idx += sprintf(sql_qry+idx, "%s", "	BLDNO_SUB,                           ");
	idx += sprintf(sql_qry+idx, "%s", "	EMD_SERIAL,                          ");
	idx += sprintf(sql_qry+idx, "%s", "	MOVE_CODE                            ");
	idx += sprintf(sql_qry+idx, "%s", ") VALUES (                              ");
	idx += sprintf(sql_qry+idx, "%s", "	:BJD_CD,                             ");
	idx += sprintf(sql_qry+idx, "%s", "	:SIDO_NM,                            ");
	idx += sprintf(sql_qry+idx, "%s", "	:SIGG_NM,                            ");
	idx += sprintf(sql_qry+idx, "%s", "	:EMD_NM,                             ");
	idx += sprintf(sql_qry+idx, "%s", "	:RI_NM,                              ");
	idx += sprintf(sql_qry+idx, "%s", "	:SAN_CK,                             ");
	idx += sprintf(sql_qry+idx, "%s", "	:JIBUN_MAIN,                         ");
	idx += sprintf(sql_qry+idx, "%s", "	:JIBUN_SUB,                          ");
	idx += sprintf(sql_qry+idx, "%s", "	:RD_CD,                              ");
	idx += sprintf(sql_qry+idx, "%s", "	:GRND_CK,                            ");
	idx += sprintf(sql_qry+idx, "%s", "	:BLDNO_MAIN,                         ");
	idx += sprintf(sql_qry+idx, "%s", "	:BLDNO_SUB,                          ");
	idx += sprintf(sql_qry+idx, "%s", "	:EMD_SERIAL,                         ");
	idx += sprintf(sql_qry+idx, "%s", "	:MOVE_CODE                           ");
	idx += sprintf(sql_qry+idx, "%s", "); ");
   
	
	strcpy (stmt, sql_qry);
	//printf("%s\n", sql_qry);

	ret = ora_connect_tns("s_test/s_test@(DESCRIPTION=(ADDRESS_LIST=(ADDRESS=(PROTOCOL=TCP)(HOST=168.150.182.72)(PORT=1521)))(CONNECT_DATA=(SERVER=DEDICATED)(SERVICE_NAME=STEST)))");
	
	if(ret == SUCCESS)
	{
		printf("success!!!\n");
	}
	
	ret = ora_setstmt (stmt);
	
	if(ret == SUCCESS)
	{
		printf("success!!!\n");
	}

	
	/*오류 나는 부분 여기 잡아야!!!!*/
	ret = ora_bind_u_params (
		"%s %s %s %s %s %s %s %s %s %s %s %s %s %s", "2911012200","광주광역시","동구","학동","","0","81","0","291102009001","0","15","0","2967", ""); 
		//"%s %s %s %s %s %s %s %s %s %s %s %s %s %s", "2911012200","dddd","sss","aaa","00","0","81","0","291102009001","0","15","0","2967","aa"); 
		//"%s %s %s %s %s %s %s %s %s %s %s %s %s", "2911012200","dddd","sss","aaa","4","0","81","0","291102009001","0","15","0","2967"); 
	
	
	ret = ora_execute (&ncols);
	
	if(ret == SUCCESS)
	{
		printf("insert success!!![%d]\n", ncols);
	}
	
	ret = ora_disconnect (ROLLBACK);
	
	exit (EXIT_SUCCESS);
}


int main (void)
{
	
	int ret;
	
	//ret = test_select();
	
	//ret = test_arg_select ();
	ret = test_arg_auto_insert();
	//ret = test_arg_auto_select();
	
	
	return ret;
}
