/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <stdio.h>
#include "csk_malloc.h"
uint64_t value = 1715330096;
uint32_t value1 = 12345;
static struct k_work_q aiui_work_q;
static void aui_init_work_handler(struct k_work *work);
char data[22] = {0};

static void aui_init_work_handler(struct k_work *work)
{
	printk("value is llu %llu\n", value);
	printk("value1 is llu %d\n", value1);
	// printk("addr is %p",value);
	printk("\n\n");

}

void wifi_connect_task(void *p1, void *p2, void *p3){

	while(1){
		printk("value is llu %llu\n", value);
		printk("value is llu %llu\n", value);
		k_msleep(1000);
	}
}
static int wifi_connect_task_init(void)
{
        k_thread_stack_t *stack;
        k_tid_t tid;
        const int stack_size = 2 * 1024;
        const int thread_prio = 2;

        stack = csk_malloc(stack_size);
        if (stack == NULL) {
                printk("app obj rec stack malloc failed");
                return -ENOMEM;
        }

        struct k_thread *new_thread = csk_malloc(sizeof(struct k_thread));
        if (new_thread == NULL) {
                csk_free(stack);
                return -ENOMEM;
        }

        tid = k_thread_create(new_thread, stack, stack_size, wifi_connect_task, NULL, NULL, NULL,
                              thread_prio, 0, K_NO_WAIT);
        if (tid != new_thread) {
                csk_free(new_thread);
                csk_free(stack);
                printk("obj rec thread create failed: %p", tid);
                return -EFAULT;
        }

        k_thread_name_set(tid, "wifi_connect");
        printk("obj rec thread created successfully");

        return 0;
}

K_WORK_DEFINE(aiui_init_work, aui_init_work_handler);
int main(void)
{

	wifi_connect_task_init();
	while(1){
		k_msleep(1000);
		printk("123value is llu %llu\n", value);
		printk("456value is llu %llu\n", value);

	}
	return 0;
}
