/*
** libzbxpgsql - A PostgreSQL monitoring module for Zabbix
** Copyright (C) 2015 - Ryan Armstrong <ryan@cavaliercoder.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**/

#include "libzbxpgsql.h"

#define PGSQL_GET_VERSION           "SELECT version();"

#define PGSQL_GET_STARTTIME         "SELECT pg_postmaster_start_time();"

#define PGSQL_GET_UPTIME            "SELECT EXTRACT(EPOCH FROM NOW()) - EXTRACT(EPOCH FROM pg_postmaster_start_time());"

/*
 * Custom key pg.connect
 *
 * Returns 1 if the Zabbix Agent can connect to PostgreSQL instance
 *
 * Parameters:
 *   0:  connection string
 *   1:  connection database
 *
 * Returns: b
 */
int    PG_CONNECT(AGENT_REQUEST *request, AGENT_RESULT *result)
{
    int             ret = SYSINFO_RET_FAIL;             // Request result code
    const char          *__function_name = "PG_CONNECT";        // Function name for log file
    PGconn      *conn = NULL;
    
    zabbix_log(LOG_LEVEL_DEBUG, "In %s()", __function_name);
    
    conn = pg_connect_request(request);
            
    if(NULL != conn && CONNECTION_OK == PQstatus(conn)) {
        SET_UI64_RESULT(result, 1);
        PQfinish(conn);
    }
    else {
        SET_UI64_RESULT(result, 0);
    }
    
    // Set result    
    ret = SYSINFO_RET_OK;
    
    zabbix_log(LOG_LEVEL_DEBUG, "End of %s()", __function_name);
    return ret;
}

/*
 * Custom key pg.version
 *
 * Returns the version string of the connection PostgreSQL Server, E.g.:
 *  PostgreSQL 9.4.4 on x86_64-unknown-linux-gnu, compiled by gcc 
 *  (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3, 64-bit
 *
 * Parameters:
 *   0:  connection string
 *   1:  connection database
 *
 * Returns: s
 */
int    PG_VERSION(AGENT_REQUEST *request, AGENT_RESULT *result)
{
    int             ret = SYSINFO_RET_FAIL;             // Request result code
    const char      *__function_name = "PG_VERSION";    // Function name for log file
    
    zabbix_log(LOG_LEVEL_DEBUG, "In %s()", __function_name);
    
    ret = pg_get_string(request, result, PGSQL_GET_VERSION, NULL);
    
    zabbix_log(LOG_LEVEL_DEBUG, "End of %s()", __function_name);
    return ret;
}

/*
 * Custom key pg.starttime
 *
 * Returns the start time of the postmaster daemon. E.g.
 *  2015-08-08 08:00:17.894706+00
 *
 * Parameters:
 *   0:  connection string
 *   1:  connection database
 *
 * Returns: s
 */
int    PG_STARTTIME(AGENT_REQUEST *request, AGENT_RESULT *result)
{
    int             ret = SYSINFO_RET_FAIL;            // Request result code
    const char      *__function_name = "PG_STARTTIME"; // Function name for log file
    
    char            *query = PGSQL_GET_STARTTIME;
    
    zabbix_log(LOG_LEVEL_DEBUG, "In %s()", __function_name);
    
    ret = pg_get_string(request, result, query, NULL);
    
    zabbix_log(LOG_LEVEL_DEBUG, "End of %s()", __function_name);
    return ret;
}

/*
 * Custom key pg.uptime
 *
 * Returns the uptime of the postmaster daemon in second. E.g.
 *  86400
 *
 * Parameters:
 *   0:  connection string
 *   1:  connection database
 *
 * Returns: u
 */
int    PG_UPTIME(AGENT_REQUEST *request, AGENT_RESULT *result)
{
    int             ret = SYSINFO_RET_FAIL;         // Request result code
    const char      *__function_name = "PG_UPTIME"; // Function name for log file
    
    char            *query = PGSQL_GET_UPTIME;
    
    zabbix_log(LOG_LEVEL_DEBUG, "In %s()", __function_name);
    
    ret = pg_get_int(request, result, query, NULL);
    
    zabbix_log(LOG_LEVEL_DEBUG, "End of %s()", __function_name);
    return ret;
}
