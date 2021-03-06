/*
 * Copyright (c) 2000, 2001, 2002, 2003, 2004, 2005, 2008, 2009
 *	The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * rmdir
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include "config.h"
#include "test.h"

static
int
rmdir_file(void)
{
	int rv;
	int result;

	report_begin("rmdir a file");
	if (create_testfile()<0) {
		report_aborted(&result);
		return result;
	}
	rv = rmdir(TESTFILE);
	result = report_check(rv, errno, ENOTDIR);
	remove(TESTFILE);

	return result;
}

static
int
rmdir_dot(void)
{
	int rv;
	int result;

	report_begin("rmdir .");
	rv = rmdir(".");
	result = report_check(rv, errno, EINVAL);
	return result;
}

static
int
rmdir_dotdot(void)
{
	int rv;

	report_begin("rmdir ..");
	rv = rmdir("..");
	return report_check2(rv, errno, EINVAL, ENOTEMPTY);
}

static
int
rmdir_empty(void)
{
	int rv;

	report_begin("rmdir empty string");
	rv = rmdir("");
	return report_check(rv, errno, EINVAL);
}

void
test_rmdir(void)
{
	int ntests = 0, lost_points = 0;
	int result;

	test_rmdir_path(&ntests, &lost_points);

	ntests++;
	result = rmdir_file();
	handle_result(result, &lost_points);

	ntests++;
	result = rmdir_dot();
	handle_result(result, &lost_points);

	ntests++;
	result = rmdir_dotdot();
	handle_result(result, &lost_points);

	ntests++;
	result = rmdir_empty();
	handle_result(result, &lost_points);

	if(!lost_points)
		success(TEST161_SUCCESS, SECRET, "/testbin/badcall");
}
