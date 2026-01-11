/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatsato <tatsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:00:00 by claude            #+#    #+#             */
/*   Updated: 2025/06/16 00:00:00 by claude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interfaces/output_interface.h"
#include "utils/libft_custom.h"
#include <stdlib.h>
#include <unistd.h>

t_output_result	impl_write_fd(int fd, const char *message)
{
	if (!message || fd < 0)
		return (OUTPUT_ERROR_WRITE);
	if (write(fd, message, ft_strlen(message)) == -1)
		return (OUTPUT_ERROR_SYSTEM);
	return (OUTPUT_SUCCESS);
}

void	destroy_output_service(t_output_service *service)
{
	if (service)
		free(service);
}
