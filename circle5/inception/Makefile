HOSTS_SETUP_SH=./srcs/requirements/tools/hosts.sh
VOLUME_SETUP_SH=./srcs/requirements/tools/volume.sh
FCLEAN_SETUP_SH=./srcs/requirements/tools/fclean.sh
TOOLS_SH_PATH = ./srcs/requirements/tools/

DOCKER_COMPOSE_FILE = ./srcs/docker-compose.yml
DOCKER_COMPOSE = docker compose --file $(DOCKER_COMPOSE_FILE)

all: up

up:
	@chmod +x $(VOLUME_SETUP_SH)
	@chmod +x $(HOSTS_SETUP_SH)
	@chmod +x $(addsuffix info.sh, $(TOOLS_SH_PATH))
	@chmod +x $(addsuffix fclean.sh, $(TOOLS_SH_PATH))
	@$(VOLUME_SETUP_SH)
	@$(HOSTS_SETUP_SH)
	$(DOCKER_COMPOSE) up -d --build

down:
	$(DOCKER_COMPOSE) down --volumes

clean:
	sudo docker-compose -f srcs/docker-compose.yml down -v --rmi all --remove-orphans
	$(DOCKER_COMPOSE) down --rmi all --volumes

fclean: clean
	sudo rm -rf ${HOME}/data
	sudo docker system prune --volumes --all --force
	sudo docker network prune --force
	sudo docker volume prune --force
	@$(FCLEAN_SETUP_SH)

re:
	@make fclean
	@make all

.PHONY: all up down clean fclean re