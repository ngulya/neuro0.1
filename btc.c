/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 14:12:37 by ngulya            #+#    #+#             */
/*   Updated: 2017/08/23 14:12:38 by ngulya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n.h"

double	method_er(neuro **n, double *must)
{
	double	delta_o[(*n)->ou];
	double	delta_h2[(*n)->hi2];
	double	delta_h1[(*n)->hi1];
	double	tmp;
	double	res;
	double	nu;
	int 	i;
	int 	j;
	int 	s;

	nu = 0.00001;
	s = 0;
	tmp = 0;
	while(s < (*n)->ou)
	{
		delta_o[s] = must[s] - (*n)->output[s];
		tmp += delta_o[s] * delta_o[s];
		s++;
	}
	res = tmp / 2;
	s = 0;
	i = 0;
	while(i < (*n)->hi2)
	{
		j = 0;
		delta_h2[i] = 0;
		while(j < (*n)->ou)
		{
			delta_h2[i] += delta_o[j] * (*n)->w_h2[i][j];
			j++;
		}
		i++;
	}
	i = 0;
	while(i < (*n)->hi1)
	{
		j = 0;
		delta_h1[i] = 0;
		while(j < (*n)->hi2)
		{
			delta_h1[i] += delta_h2[j] * (*n)->w_h1[i][j];
			j++;
		}
		i++;
	}
	i = 0;
	while(i < (*n)->hi1)
	{
		j = 0;
		while(j < (*n)->in + 1)
		{
			if(j == (*n)->in)
				tmp = 1;
			else
				tmp = (*n)->input[j];
			(*n)->w_i[j][i] += nu * delta_h1[i] * (*n)->hidden1[i] * (1 - (*n)->hidden1[i]) * tmp;
			j++;
		}
		i++;
	}

	i = 0;
	while(i < (*n)->hi2)
	{
		j = 0;
		while(j < (*n)->hi1 + 1)
		{
			if(j == (*n)->hi1)
				tmp = 1;
			else
				tmp = (*n)->hidden1[j];
			(*n)->w_h1[j][i] += nu * delta_h2[i] * (*n)->hidden2[i] * (1 - (*n)->hidden2[i]) * tmp;
			j++;
		}
		i++;
	}

	i = 0;
	while(i < (*n)->ou)
	{
		j = 0;
		while(j < (*n)->hi2 + 1)
		{
			if(j == (*n)->hi2)
				tmp = 1;
			else
				tmp = (*n)->hidden2[j];
			(*n)->w_h2[j][i] += nu * delta_o[i] * (*n)->output[i] * (1 - (*n)->output[i]) * tmp;
			j++;
		}
		i++;
	}
	return res;
}

void	sdvig(neuro **n, double *must, int num)
{
	int 	in;
	int 	i;

	in = (*n)->in;
	i = 0;
	while(i + num < in)
	{
		(*n)->input[i] = (*n)->input[i + num];
		i++;
	}
	num = 0;
	while(i < in)
	{
		(*n)->input[i] = must[num];
		i++;
		num++;
	}
}

int		main(int argc, char **argv)
{
	neuro 	*n;
	FILE 	*fp;
	double	real;
	double	*m;
	int 	fora;
	int 	tmp;
	int 	f;
	int 	i;
	int 	num_out;

	num_out = 2;
	fora = 0;
	real = 0;
	f = 18;
	n = give_memory(16,48,24,num_out);
	fp = fopen("smallb.csv", "r");
	printf("1 - read from file\n");
	scanf("%d", &tmp);
	if(tmp == 1)
		write_from_file(&n);
	else
		zero(&n);
	tmp = 0;
	printf("1 - start study\n");
	scanf("%d", &fora);
	if(fora == 1)
	{
		while(tmp < 4000000)//40000
		{
			if(f >= 104)
			{
				fclose(fp);
				fp = fopen("smallb.csv", "r");
				f = 18;
				printf("%0.16lf	%d\n", real,tmp);
			}
			if(f == 18)
			{
				real = 0;
				read_btc(fp, 16, &n);
				calculate(&n);
				m = read_must(fp, num_out);
				method_er(&n, m);
			}
			sdvig(&n, m, 2);
			calculate(&n);
			m = read_must(fp, num_out);
			real += method_er(&n, m);
			free(m);
			tmp++;
			f += 2;
		}
	}
	fclose(fp);

	printf("prediction on history\n");
	fp = fopen("smallb.csv", "r");
	f = 18;
	while(f < 104)
	{
		if(f == 18)
		{
			read_btc(fp, 16, &n);
			calculate(&n);
			m = read_must(fp, num_out);
			i = 0;
			while(i < num_out)
			{
				printf("%f   must = %f\n", n->output[i] * 10000, m[i]* 10000);
				i++;
			}
			printf("\n");
		}
		sdvig(&n, m, 2);
		calculate(&n);
		m = read_must(fp, num_out);
		i = 0;
		while(i < num_out)
		{
			printf("[%f]    %f = must\n", n->output[i] * 10000, m[i]* 10000);
			i++;
		}
		printf("\n");
		free(m);
		tmp++;
		f += 2;
	}

	fp = fopen("now.csv", "r");
	f = 0;
	printf("now.csv\n");
	read_btc(fp, 16, &n);
	calculate(&n);
	i = 0;
	while(i < num_out)
	{
		printf("%f\n", n->output[i] * 10000);
		i++;
	}
	printf("\n");
	fclose(fp);
	
	if(fora == 1)
	{
		printf("If you wont write data in file press - 1\n");
		tmp = 0;
		scanf("%d", &tmp);
		if(tmp == 1)
			write_file(n);
	}
	
	free_neuro(&n);
}