/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 14:12:57 by ngulya            #+#    #+#             */
/*   Updated: 2017/08/23 14:12:58 by ngulya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_H
#define N_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct			mgk
{
	int					in;
	int					hi1;
	int					hi2;
	int					ou;
	double				*input;
	double				*hidden1;
	double				*hidden2;
	double				*output;
	double				**w_i;
	double				**w_h1;
	double				**w_h2;
}						neuro;

neuro					*give_memory(int in_g, int hi1_g, int hi2_g, int ou_g);
void					zero(neuro **n);
void					vuvod(neuro *n);
void					write_from_file(neuro **n);
void					write_file(neuro *n);
void					calculate(neuro **n);
double					randm(void);
double					sigmoid(double n);
void					read_btc(FILE *fp, int i, neuro **n);
double					*read_must(FILE *fp, int i);
void					free_neuro(neuro **n);

#endif
