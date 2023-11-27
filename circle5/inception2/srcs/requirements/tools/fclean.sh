#!/bin/bash

wordpress_path=$($(pwd)/srcs/requirements/tools/info.sh wordpress_path)
mariadb_path=$($(pwd)/srcs/requirements/tools/info.sh mariadb_path)
conf=$($(pwd)/srcs/requirements/tools/info.sh conf)
hosts_path=$($(pwd)/srcs/requirements/tools/info.sh hosts_path)

rm -rf ${wordpress_path}
rm -rf ${mariadb_path}


# * ----------------------------------------------------------
if [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    sed -i "/${conf}/d" ${hosts_path}
fi
# * ----------------------------------------------------------

echo "\
--------------------

@fclean done

--------------------"
