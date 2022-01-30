/*
 * @Description: 
 * @Autor: Weihang Shen
 * @Date: 2022-01-26 00:14:44
 * @LastEditors: Weihang Shen
 * @LastEditTime: 2022-01-30 16:22:02
 */

#include <fcntl.h>
#include <sys/stat.h>

#include "log.h"
#include "UAServer.h"

int main(int argc,char *argv[])
{
    int config_fd = open(argv[1], O_RDONLY|O_NDELAY);
    if (config_fd < 0) {
        LOG_ERROR("Fail to open config json file: %s", argv[1]);
    }
    struct stat *config_stat = (struct stat *)malloc(sizeof(struct stat));
    stat(argv[1], config_stat);
    char *config_buf = (char *)malloc(config_stat->st_size);
    int read_count = read(config_fd, config_buf, config_stat->st_size);
    if (read_count != config_stat->st_size) {
        LOG_ERROR("Fail to read from config json file: %s", argv[1]);
    }
    close(config_fd);
    free(config_stat);
    
    OPCUA_Server *server = (OPCUA_Server *)malloc(sizeof(OPCUA_Server));
    init_server(server, config_buf);
    start_server(server);
    return 0;
}