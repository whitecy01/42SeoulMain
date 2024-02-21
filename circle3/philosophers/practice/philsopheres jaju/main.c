/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:32:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/13 19:17:37 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

		pthread_create(&(info->philo[i].thread), NULL, action_thread, &(info->philo[i]));
		i++;
	}
	ft_philo_check_finish(info->philo);
	i = 0;
	while (i < info->philo_number)
	{
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
	//free
	//죽는 거 
	return (0);
}



int	main(int argc, char **argv)
{
	t_info info;
	//argc가 5와 6 밖에 있을 때 error
	if (!(argc >= 5 && argc <= 6))
	{
		print_error("Wrong argc\n");
		return (1);
	}
	//argv 인자값 atoi처리
	if (init(&info, argv, argc))
	{
		print_error("Wrong argv\n");
		return (1);
	}
	//필로 1명일때
	//1명일 때는 포크가 하나 
	//fork[i], fork [(i + 1) % n] -> 2개의 포크(오른쪽, 왼쪽)가 같은 거 인지
	
	//뮤텍스 init
	//쓰레드 액션
	ft_philo_start(&info);
	
}

