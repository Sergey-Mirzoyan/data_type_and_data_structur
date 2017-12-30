#include <math.h>

#include "pp_list.h"
#include "rand_comp.h"

#define OUT_MAX 1000

int main(void)
{
    int min = 1;
    int max = 5;
    
    int x;
    
    double t1_b = 1;
    double t1_e = 5;
    double t2_b = 0;
    double t2_e = 3;
    double t3_b = 0;
    double t3_e = 4;
    double t4_b = 0;
    double t4_e = 1;

    int period = 100;
    int per = 100;

    srand(time(NULL));
    setbuf(stdout, NULL);
    
    char ch;

    //printf("Изменить параметры очереди [Y/n]: ");
    //scanf("%c", &ch);
    //getc(stdin);

    int flag_addr = 0;

    printf("Выводить выделенные и освобожденные адреса [Y/n]: ");
    scanf("%c", &ch);
    getc(stdin);
    
    if (ch == 'y' || ch == 'Y')
	    flag_addr = 1;

    struct queue *q_1 = malloc(sizeof(struct queue));
    struct queue *q_2;
    
    if (q_1)
    {
        init(q_1);

        q_2 = malloc(sizeof(struct queue));

        if (q_2)
        {
            init(q_2);

            int cn_in_1 = 0; // Количество значений добавленных в 1-ую очередь
            int cn_out_1 = 0; // Количество обработанных значений 1-го типа
            int cn_in_2 = 0; // Количество значений добавленных во 2-ую очередь
            int cn_out_2 = 0; // Количество обработанных значений 2-го типа
            int cn_del = 0; // Количество выброшенных заявок 2-го типа
            int cn_do = 0; // Количество значений отправленных в ОА

            double downtime = 0; // Время простоя

            //double new_t;

            int oa_do = 0; // Флаг ОА
            // 0 - ничего не обрабатывается
            // 1 - обрабатывается значение 1-го типа
            // 2 - обрабатывается значение 2-го типа

            double t1, t2, t3, t4;
            double t = 0;
            double t_do = 0;

            t1 = get_rand(t1_b, t1_e);
            t2 = get_rand(t2_b, t2_e);
            t3 = get_rand(t3_b, t3_e);
            t4 = get_rand(t4_b, t4_e);

            int eq_1, eq_2;

            while (cn_out_1 != OUT_MAX)
            {
                if (cn_out_1 == per)
                {
                    printf("cn_out_1 = %d\n", cn_out_1);
                    printf("len_q_1 = %d\n", len_queue(q_1));
                    printf("len_q_2 = %d\n", len_queue(q_2));
                    printf("\n");

                    if (flag_addr == 1)
                    {
                        printf("Выделенные адреса 1-ой очереди:\n");
                        print_addr(q_1, 1);    
                        printf("\n");

                        printf("Освобожденные адреса 1-ой очереди:\n");
                        print_addr(q_1, 2);
                        printf("\n");

                        printf("Выделенные адреса 2-ой очереди:\n");
                        print_addr(q_2, 1);
                        printf("\n");

                        printf("Освобожденные адреса 2-ой очереди:\n");
                        print_addr(q_2, 2);
                        printf("\n");
                    }

                    per += period;
                }

                eq_1 = compare_double(&t1, &t2);

                if (eq_1 == 0) // T1 = T2
                {
                    if (oa_do == 0)
                    {
                        push(q_1, get_rand_range_int(min, max));
                        cn_in_1++;
                        
                        push(q_2, get_rand_range_int(min, max));
                        cn_in_2++;

                        pop(q_1, &x);
                        cn_do++;
                        oa_do = 1;

                        downtime += t1;
                        t += t1;

                        t1 = get_rand(t1_b, t1_e);
                        t2 = get_rand(t2_b, t2_e);
                    }
                    else if (oa_do == 1)
                    {
                        eq_2 = compare_double(&t1, &t3);

                        if (eq_2 == 0) // T1 = T2 = T3
                        {
                            cn_out_1++;
                            oa_do = 0;
                                
                            push(q_1, get_rand_range_int(min, max));
                            cn_in_1++;

                            push(q_2, get_rand_range_int(min, max));
                            cn_in_2++;

                            pop(q_1, &x);
                            
                            cn_do++;
                            oa_do = 1;

                            t_do += t3;
                            t += t1;

                            t1 = get_rand(t1_b, t1_e);
                            t2 = get_rand(t2_b, t2_e);
                            t3 = get_rand(t3_b, t3_e);
                        }
                        else if (eq_2 > 0) // T1 = T2 > T3
                        {
                            cn_out_1++;
                            oa_do = 0;

                            if (len_queue(q_1) > 0)
                            {
                                pop(q_1, &x);
                                cn_do++;
                                oa_do = 1;
                            }
                            else if (len_queue(q_2) > 0)
                            {
                                pop(q_2, &x);
                                cn_do++;
                                oa_do = 2;
                            }
                            else
                            {
                                oa_do = 0;
                            }

                            t1 -= t3;
                            t2 -= t3;

                            t_do += t3;
                            t += t3;

                            t3 = get_rand(t3_b, t3_e);
                        }
                        else if (eq_2 < 0) // T1 = T2 < T3
                        {
                            push(q_1, get_rand_range_int(min, max));
                            cn_in_1++;
                            
                            push(q_2, get_rand_range_int(min, max));
                            cn_in_2++;

                            t3 -= t1;

                            t_do += t1;
                            t += t1;

                            t1 = get_rand(t1_b, t1_e);
                            t2 = get_rand(t2_b, t2_e);
                        }
                    }
                    else if (oa_do == 2)
                    {
                        eq_2 = compare_double(&t1, &t4);

                        if (eq_2 == 0) // T1 = T2 = T4
                        {
                            cn_out_2++;
                            oa_do = 0;

                            push(q_1, get_rand_range_int(min, max));
                            cn_in_1++;
                            
                            push(q_2, get_rand_range_int(min, max));
                            cn_in_2++;
                            
                            pop(q_1, &x);
                            
                            cn_do++;
                            oa_do = 1;

                            t_do += t4;
                            t += t1;

                            t1 = get_rand(t1_b, t1_e);
                            t2 = get_rand(t2_b, t2_e);
                            t4 = get_rand(t4_b, t4_e);
                        }
                        else if (eq_2 > 0) // T1 = T2 > T4
                        {
                            cn_out_2++;
                            oa_do = 0;

                            if (len_queue(q_1) > 0)
                            {
                                pop(q_1, &x);
                                cn_do++;
                                oa_do = 1;
                            }
                            else if (len_queue(q_2) > 0)
                            {
                                pop(q_2, &x);
                                cn_do++;
                                oa_do = 2;
                            }
                            else
                            {
                                oa_do = 0;
                            }

                            t1 -= t4;
                            t2 -= t4;

                            t_do += t4;
                            t += t4;

                            t4 = get_rand(t4_b, t4_e);
                        }
                        else if (eq_2 < 0) // T1 = T2 < T4
                        {
                            push(q_1, get_rand_range_int(min, max));
                            cn_in_1++;
                            
                            push(q_2, get_rand_range_int(min, max));
                            cn_in_2++;

                            push(q_2, x);
                            cn_in_2++;
                            cn_del++;
                            oa_do = 0;

                            pop(q_1, &x);
                            cn_do++;
                            oa_do = 1;

                            t_do += t1;
                            t += t1;

                            t1 = get_rand(t1_b, t1_e);
                            t2 = get_rand(t2_b, t2_e);
                            t4 = get_rand(t4_b, t4_e);
                        }
                    }
                }
                else if (eq_1 > 0) // T1 > T2
                {
                    if (oa_do == 0)
                    {
                        push(q_2, get_rand_range_int(min, max));
                        cn_in_2++;
                        
                        if (len_queue(q_1) > 0)
                        {
                            pop(q_1, &x);
                            cn_do++;
                            oa_do = 1;
                        }
                        else
                        {
                            pop(q_2, &x);
                            cn_do++;
                            oa_do = 2;
                        }

                        t1 -= t2;

                        downtime += t2;
                        t += t2;

                        t2 = get_rand(t2_b, t2_e);
                    }
                    else if (oa_do == 1)
                    {
                        eq_2 = compare_double(&t2, &t3);

                        if (eq_2 == 0) // T1 > T2 = T3
                        {
                            cn_out_1++;
                            oa_do = 0;

                            push(q_2, get_rand_range_int(min, max));
                            cn_in_2++;
                           
                            if (len_queue(q_1) > 0)
                            {
                                pop(q_1, &x);
                                cn_do++;
                                oa_do = 1;
                            }
                            else
                            {
                                pop(q_2, &x);
                                cn_do++;
                                oa_do = 2;
                            }

                            t1 -= t2;

                            t_do += t3;
                            t += t2;

                            t2 = get_rand(t2_b, t2_e);
                            t3 = get_rand(t3_b, t3_e);
                        }
                        else if (eq_2 > 0) // T1 > T2 > T3
                        {
                            cn_out_1++;
                            oa_do = 0;

                            if (len_queue(q_1) > 0)
                            {
                                pop(q_1, &x);
                                cn_do++;
                                oa_do = 1;
                            }
                            else if (len_queue(q_2) > 0)
                            {
                                pop(q_2, &x);
                                cn_do++;
                                oa_do = 2;
                            }
                            else
                            {
                                oa_do = 0;
                            }

                            t1 -= t3;
                            t2 -= t3;

                            t_do += t3;
                            t += t3;

                            t3 = get_rand(t3_b, t3_e);
                        }
                        else if (eq_2 < 0) // T1 > T2 < T3
                        {
                            push(q_2, get_rand_range_int(min, max));
                            cn_in_2++;
                            
                            t1 -= t2;
                            t3 -= t2;

                            t_do += t2;
                            t += t2;

                            t2 = get_rand(t2_b, t2_e);
                        }
                    }
                    else if (oa_do == 2)
                    {
                        eq_2 = compare_double(&t2, &t4);

                        if (eq_2 == 0) // T1 > T2 = T4
                        {
                            cn_out_2++;
                            oa_do = 0;

                            push(q_2, get_rand_range_int(min, max));
                            cn_in_2++;
                            
                            if (len_queue(q_1) > 0)
                            {
                                pop(q_1, &x);
                                cn_do++;
                                oa_do = 1;
                            }
                            else
                            {
                                pop(q_2, &x);
                                cn_do++;
                                oa_do = 2;
                            }

                            t1 -= t2;

                            t_do += t4;
                            t += t2;

                            t2 = get_rand(t2_b, t2_e);
                            t4 = get_rand(t4_b, t4_e);
                        }
                        else if (eq_2 > 0) // T1 > T2 > T4
                        {
                            cn_out_2++;
                            oa_do = 0;

                            if (len_queue(q_1) > 0)
                            {
                                pop(q_1, &x);
                                cn_do++;
                                oa_do = 1;
                            }
                            else if (len_queue(q_2) > 0)
                            {
                                pop(q_2, &x);
                                cn_do++;
                                oa_do = 2;
                            }
                            else
                            {
                                oa_do = 0;
                            }

                            t1 -= t4;
                            t2 -= t4;

                            t_do += t4;
                            t += t4;

                            t4 = get_rand(t4_b, t4_e);
                        }
                        else if (eq_2 < 0) // T1 > T2 < T4
                        {
                            push(q_2, get_rand_range_int(min, max));
                            cn_in_2++;
                            
                            t1 -= t2;
                            t4 -= t2;

                            t_do += t2;
                            t += t2;

                            t2 = get_rand(t2_b, t2_e);
                        }
                    }
                }
                else if (eq_1 < 0) // T1 < T2
                {
                    if (oa_do == 0)
                    {
                        push(q_1, get_rand_range_int(min, max));
                        cn_in_1++;
                        
                        pop(q_1, &x);
                        cn_do++;
                        oa_do = 1;

                        t2 -= t1;

                        downtime += t1;
                        t += t1;

                        t1 = get_rand(t1_b, t1_e);
                    }
                    else if (oa_do == 1)
                    {
                        eq_2 = compare_double(&t1, &t3);

                        if (eq_2 == 0) // T2 > T1 = T3
                        {
                            cn_out_1++;
                            oa_do = 0;

                            push(q_1, get_rand_range_int(min, max));
                            cn_in_1++;
                            
                            pop(q_1, &x);
                            cn_do++;
                            oa_do = 1;

                            t2 -= t1;

                            t_do += t3;
                            t += t1;

                            t1 = get_rand(t1_b, t1_e);
                            t3 = get_rand(t3_b, t3_e);
                        }
                        else if (eq_2 > 0) // T2 > T1 > T3
                        {
                            cn_out_1++;
                            oa_do = 0;

                            if (len_queue(q_1) > 0)
                            {
                                pop(q_1, &x);
                                
                                cn_do++;
                                oa_do = 1;
                            }
                            else if (len_queue(q_2) > 0)
                            {
                                pop(q_2, &x);
                                cn_do++;
                                oa_do = 2;
                            }
                            else
                            {
                                oa_do = 0;
                            }

                            t1 -= t3;
                            t2 -= t3;

                            t_do += t3;
                            t += t3;

                            t3 = get_rand(t3_b, t3_e);
                        }
                        else if (eq_2 < 0) // T2 > T1 < T3
                        {
                            push(q_1, get_rand_range_int(min, max));
                            cn_in_1++;
                            
                            t2 -= t1;
                            t3 -= t1;

                            t_do += t1;
                            t += t1;

                            t1 = get_rand(t1_b, t1_e);
                        }
                    }
                    else if (oa_do == 2)
                    {
                        eq_2 = compare_double(&t1, &t4);

                        if (eq_2 == 0) // T2 > T1 = T4
                        {
                            cn_out_2++;
                            oa_do = 0;
                            
                            push(q_1, get_rand_range_int(min, max));
                            cn_in_1++;

                            pop(q_1, &x);
                            cn_do++;
                            oa_do = 1;

                            t2 -= t1;

                            t_do += t4;
                            t += t1;

                            t1 = get_rand(t1_b, t1_e);
                            t4 = get_rand(t4_b, t4_e);
                        }
                        else if (eq_2 > 0) // T2 > T1 > T4
                        {
                            cn_out_2++;
                            oa_do = 0;

                            if (len_queue(q_1) > 0)
                            {
                                pop(q_1, &x);
                                cn_do++;
                                oa_do = 1;
                            }
                            else if (len_queue(q_2) > 0)
                            {
                                pop(q_2, &x);
                                cn_do++;
                                oa_do = 2;
                            }
                            else
                            {
                                oa_do = 0;
                            }

                            t1 -= t4;
                            t2 -= t4;

                            t_do += t4;
                            t += t4;

                            t4 = get_rand(t4_b, t4_e);
                        }
                        else if (eq_2 < 0) // T2 > T1 < T4
                        {
                            push(q_1, get_rand_range_int(min, max));
                            cn_in_1++;

                            push(q_2, x);
                            cn_in_2++;
                            cn_del++;
                            oa_do = 0;

                            pop(q_1, &x);
                            cn_do++;
                            oa_do = 1;

                            t2 -= t1;

                            t_do += t1;
                            t += t1;

                            t1 = get_rand(t1_b, t1_e);
                            t4 = get_rand(t4_b, t4_e);
                        }
                    }
                }
            }

            printf("t = %.2lf\n", t);
            printf("t_do = %.2lf\n", t_do);
            printf("downtime = %.2lf\n", downtime);
            printf("cn_in_1 = %d\n", cn_in_1);
            printf("cn_in_2 = %d\n", cn_in_2 - cn_del);
            printf("cn_out_1 = %d\n", cn_out_1);
            printf("cn_out_2 = %d\n", cn_out_2);
            printf("cn_del = %d\n", cn_del);
            printf("cn_do = %d\n", cn_do);
			printf("len_q_1 = %d\n", len_queue(q_1));
			printf("len_q_2 = %d\n", len_queue(q_2));
            
            printf("\n");
            
            double arr = t / ((t1_b + t1_e) / 2);
            //printf("Проверка по входу: %.2lf%%\n", fabs((cn_in_1 - arr) / arr) * 100);
            
            double out_t = ((t1_b + t1_e) / 2) * OUT_MAX;
            //printf("Проверка по выходу: %.2lf%%\n", fabs((t - out_t) / out_t) * 100);
            
            printf("\n");
            

            printf("cn_out_n - Количество вышедших из системы заявок n-го типа\n");
            printf("cn_in_n - Количество вошедших в n-ую очередь заявок n-го типа\n");
            printf("cn_del - Количество 'выброшенных' заявок 2-го типа\n");
            printf("cn_do - Количество срабатываний ОА\n");
            printf("t - общее время работы системы е.в.\n");
            printf("t_do - время работы ОА е.в.\n");
            printf("downtime - время простоя ОА е.в.\n");
            
            printf("\nНужно ли сравнивать push/pop  [Y/n]: ");
            char choice;
            unsigned long long time, tb, te;
            int N = 10000;
            scanf("%c", &choice);
            //scanf("%c", &choice);
            if (!(choice -'y'))
            {
                struct queue *q;
                q = malloc(sizeof(struct queue));
                init(q);
                time = 0;
                for (int i = 0; i < N; i++)
                {
                    tb = tick();
                    push(q, i);
                    te = tick();
                    
                    time += te - tb;
                }
                
                printf("Время push: %llu\n", time / N);
                
                time = 0;
                
                for (int i = 0; i < N; i++)
                {
                    tb = tick();
                    pop(q, &x);
                    te = tick();
                    
                    time += te - tb;
                }
                
                printf("Время pop: %llu\n", time / N);
                
                printf("\n");
                free(q);
            }
        }
    }
    else
        printf("Ошибка выделения памяти\n");
    
    return 0;
}
