# 多线程——interview

## synchronized

- 底层：monitor监视器锁

## Lock

底层：AQS

## AQS

定义了一套多线程访问共享资源的同步器框架

设计模式：模板模式

核心数据结构：双向链表 + state(锁状态)

定义两种资源共享方式

- 独占（如：ReentrantLock）
- 共享（如：Semaphore/CountDownLatch）

底层操作：CAS

volatile int state（代表共享资源）和一个FIFO线程等待队列

## JUC

- volatile
- atomic
- locks
- collections