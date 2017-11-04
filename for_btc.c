/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_btc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 14:12:45 by ngulya            #+#    #+#             */
/*   Updated: 2017/08/23 14:12:46 by ngulya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n.h"

double	*read_must(FILE *fp, int i)
{
	int 	j = 0;
	double	*res;

	res = (double *)malloc(sizeof(double)  * i);
	while(j < i)
	{
		fscanf(fp, "%lf", &res[j]);
		res[j] /= 10000;
		j++;
	}
	return res;
}

void	read_btc(FILE *fp, int i, neuro **n)
{
	int 	j = 0;

	while(j < i)
	{
		fscanf(fp, "%lf", &((*n)->input[j]));
		(*n)->input[j] /= 10000;
		j++;
	}
}

double	sigmoid(double n)
{
	return 1/(1 + exp(-n));
}

double	randm(void)
{
	double	a;
	int 	r;

	r = random();
	a = random();
	while(a >= 1)
		a /= 10;
	while(a >= 0.5)
		a -= 0.01;
	return (a * (r % 3 ? 1 : -1));
}


neuro					*give_memory(int in_g, int hi1_g, int hi2_g, int ou_g)
{
	neuro	*n;
	int 	tmp;

	tmp = 0;
	n = (neuro *)malloc(sizeof(neuro));
	n->in = in_g;
	n->hi1 = hi1_g;
	n->hi2 = hi2_g;
	n->ou = ou_g;
	n->input = (double *)malloc(sizeof(double) * in_g);
	n->w_i = (double **)malloc(sizeof(double *) * (in_g + 1));
	tmp = 0;
	while(tmp <	in_g + 1)
	{
		n->w_i[tmp] = (double *)malloc(sizeof(double) * hi1_g);
		tmp++;
	}
	n->hidden1 = (double *)malloc(sizeof(double) * hi1_g);
	n->w_h1 = (double **)malloc(sizeof(double *) * (hi1_g + 1));
	tmp = 0;
	while(tmp < hi1_g + 1)
	{
		n->w_h1[tmp] = (double *)malloc(sizeof(double) * hi2_g);
		tmp++;
	}
	n->hidden2 = (double *)malloc(sizeof(double) * hi2_g);
	n->w_h2 = (double **)malloc(sizeof(double *) * (hi2_g + 1));
	tmp = 0;
	while(tmp < hi2_g + 1)
	{
		n->w_h2[tmp] = (double *)malloc(sizeof(double) * ou_g);
		tmp++;
	}
	n->output = (double *)malloc(sizeof(double) * ou_g);
	return (n);
}

void	zero(neuro **n)
{
	int		tmp;
	int 	tmp2;

	tmp = 0;
	while(tmp < (*n)->in)
		(*n)->input[tmp++] = 0;
	tmp2 = 0;
	while(tmp2 < (*n)->in + 1)
	{
		tmp = 0;
		while(tmp < (*n)->hi1)
			(*n)->w_i[tmp2][tmp++] = randm();
		tmp2++;
	}

	tmp2 = 0;
	tmp = 0;
	while(tmp < (*n)->hi1)
		(*n)->hidden1[tmp++] = 0;
	while(tmp2 < (*n)->hi1 + 1)
	{
		tmp = 0;
		while(tmp < (*n)->hi2)
			(*n)->w_h1[tmp2][tmp++] = randm();
		tmp2++;
	}
	tmp = 0;
	while(tmp < (*n)->hi2)
		(*n)->hidden2[tmp++] = 0;
	tmp2 = 0;
	while(tmp2 < (*n)->hi2 + 1)
	{
		tmp = 0;
		while(tmp < (*n)->ou)
			(*n)->w_h2[tmp2][tmp++] = randm();
		tmp2++;
	}
	tmp = 0;
	while(tmp < (*n)->ou)
		(*n)->output[tmp++] = 0;
}

void	free_neuro(neuro **n)
{
	int 	tmp;

	free((*n)->input);
	free((*n)->hidden1);
	free((*n)->hidden2);
	free((*n)->output);
	tmp = 0;
	while(tmp < (*n)->in+1)
	{
		free((*n)->w_i[tmp]);
		tmp++;
	}
	free((*n)->w_i);
	tmp = 0;
	while(tmp < (*n)->hi1 + 1)
	{
		free((*n)->w_h1[tmp]);
		tmp++;
	}
	free((*n)->w_h1);
	tmp = 0;
	while(tmp < (*n)->hi2 + 1)
	{
		free((*n)->w_h2[tmp]);
		tmp++;
	}
	free((*n)->w_h2);
	free(*n);
}

void	vuvod(neuro *n)
{
	int		tmp;
	int 	tmp2;

	tmp = 0;
	printf("INPUT\n");
	while(tmp < n->in)
		printf("%f ", n->input[tmp++]);
	tmp2 = 0;
	printf("\nW_I\n");
	while(tmp2 < n->in + 1)
	{
		tmp = 0;
		while(tmp < n->hi1)
			printf("%f ",  n->w_i[tmp2][tmp++]);
		printf("\n");
		tmp2++;
	}
	tmp2 = 0;
	printf("HI1\n");
	tmp = 0;
	while(tmp < n->hi1)
		printf("%f ", n->hidden1[tmp++]);
	printf("\nW_H1\n");
	while(tmp2 < n->hi1 + 1)
	{
		tmp = 0;
		while(tmp < n->hi2)
			printf("%f ", n->w_h1[tmp2][tmp++]);
		printf("\n");
		tmp2++;
	}
	printf("HI2\n");
	tmp = 0;
	while(tmp < n->hi2)
		printf("%f ", n->hidden2[tmp++]);
	tmp2 = 0;
	printf("\nW_H2\n");
	while(tmp2 < n->hi2 + 1)
	{
		tmp = 0;
		while(tmp < n->ou)
			printf("%f ", n->w_h2[tmp2][tmp++]);
		printf("\n");
		tmp2++;
	}
	tmp = 0;
	printf("OUT\n");
	while(tmp < n->ou)
		printf("%f ", n->output[tmp++]);
	printf("\n");
}

void	write_from_file(neuro **n)
{
	int 	i;
	int 	j;

	FILE *f = fopen("data.txt", "r");
	i = 0;
	j = 0;
	while(i < (*n)->in + 1)
	{
		j = 0;
		while(j < (*n)->hi1)
			fscanf( f, "%lf", &((*n)->w_i[i][j++]));
		i++;		
	}
	j = 0;
	i = 0;
	while(i < (*n)->hi1 + 1)
	{
		j = 0;
		while(j < (*n)->hi2)
			fscanf( f, "%lf", &((*n)->w_h1[i][j++]));
		i++;
	}
	j = 0;
	i = 0;
	while(i < (*n)->hi2 + 1)
	{
		j = 0;
		while(j < (*n)->ou)
			fscanf( f, "%lf", &((*n)->w_h2[i][j++]));
		i++;
	}
	fclose(f);
}

void	write_file(neuro *n)
{
	int 	i;
	int 	j;

	FILE *f = fopen("data.txt", "w");
	i = 0;
	j = 0;
	while(i < n->in + 1)
	{
		j = 0;
		while(j < n->hi1)
			fprintf( f, "%0.16f\n", (n->w_i[i][j++]));
		i++;		
	}
	j = 0;
	i = 0;
	while(i < n->hi1 + 1)
	{
		j = 0;
		while(j < n->hi2)
			fprintf( f, "%0.16f\n", (n->w_h1[i][j++]));
		i++;
	}
	j = 0;
	i = 0;
	while(i < n->hi2 + 1)
	{
		j = 0;
		while(j < n->ou)
			fprintf( f, "%0.16f\n", (n->w_h2[i][j++]));
		i++;
	}
	fclose(f);
}


void	calculate(neuro **n)
{
	int 	j;
	int 	i;
	double	tmp;

	j = 0;
	tmp = 0;
	i = 0;
	while(i < (*n)->hi1)
	{
		j = 0;
		(*n)->hidden1[i] = 0;
		while(j < (*n)->in + 1)
		{
			if(j == (*n)->in)
				tmp = 1;
			else
				tmp = (*n)->input[j];
			(*n)->hidden1[i] += tmp * (*n)->w_i[j][i];
			j++;
		}
		i++;
	}
	i = 0;
	while(i < (*n)->hi1)
	{
		(*n)->hidden1[i] = sigmoid((*n)->hidden1[i]);
		i++;
	}
	tmp = 0;
	i = 0;
	while(i < (*n)->hi2)
	{
		j = 0;
		(*n)->hidden2[i] = 0;
		while(j < (*n)->hi1 + 1)
		{
			if(j == (*n)->hi1)
				tmp = 1;
			else
				tmp = (*n)->hidden1[j];
			(*n)->hidden2[i] += tmp * (*n)->w_h1[j][i];
			j++;
		}
		i++;
	}
	i = 0;
	while(i < (*n)->hi2)
	{
		(*n)->hidden2[i] = sigmoid((*n)->hidden2[i]);
		i++;
	}
	tmp = 0;
	i = 0;
	while(i < (*n)->ou)
	{
		j = 0;
		(*n)->output[i] = 0;
		while(j < (*n)->hi2 + 1)
		{
			if(j == (*n)->hi2)
				tmp = 1;
			else
				tmp = (*n)->hidden2[j];
			(*n)->output[i] += tmp * (*n)->w_h2[j][i];
			j++;
		}
		i++;
	}
	i = 0;
	while(i < (*n)->ou)
	{
		(*n)->output[i] = sigmoid((*n)->output[i]);
		i++;
	}
}
