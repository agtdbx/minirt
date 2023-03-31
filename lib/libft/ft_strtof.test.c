/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:07:13 by tdubois           #+#    #+#             */
/*   Updated: 2023/03/31 13:40:29 by tdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "greatest.h"
#include "libft.h"

#include <stdlib.h>
#include <float.h>
#include <math.h>

TEST	assert_matches_strtof(char const *nptr)
{
	char	*expected_endptr = NULL;
	float	expected_ret = strtof(nptr, &expected_endptr);

	char	*your_endptr = NULL;
	float	your_ret = ft_strtof(nptr, &your_endptr);
	
	if (isnanf(expected_ret))
		ASSERT(isnanf(your_ret));
	else
		ASSERT_EQ_FMT(expected_ret, your_ret, "%.20f");
	ASSERT_NEQ(NULL, your_endptr);
	ASSERT_STR_EQ(expected_endptr, your_endptr);
	PASS();
}

#define RUN_TEST_SUFFIX(suffix) ({				\
	greatest_set_test_suffix(suffix);			\
	RUN_TESTp(assert_matches_strtof, suffix);	\
	greatest_set_test_suffix(NULL);				\
})												\

SUITE (ft_strtof__suite)
{
	RUN_TEST_SUFFIX("0");
	RUN_TEST_SUFFIX("000");
	RUN_TEST_SUFFIX("123");
	RUN_TEST_SUFFIX("123.0");
	RUN_TEST_SUFFIX("123.00");
	RUN_TEST_SUFFIX("123.000");
	RUN_TEST_SUFFIX("123.0001");
	RUN_TEST_SUFFIX("123.1000");
	RUN_TEST_SUFFIX("123.0100");

	RUN_TEST_SUFFIX("lol");
	RUN_TEST_SUFFIX("123lol");
	RUN_TEST_SUFFIX("123lol123");

	RUN_TEST_SUFFIX("11111111111111111111111111111111111111111111111111111111");
	RUN_TEST_SUFFIX("0.111111111111111111111111111111111111111111111111111111");

	RUN_TEST_SUFFIX("11111111111111111111111111111111111111111111111111111111");
	RUN_TEST_SUFFIX("0.999999999999999999999999999999999999999999999999999999");
}
