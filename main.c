#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

typedef pthread_mutex_t Mutex;
typedef pthread_t Thread;

Mutex mutex;
Mutex plusM;
Mutex minusM;
Mutex mulM;
Mutex quotM;
Thread tid[20];
double first;
double second;
double third;
double dispersion = 1.000000;

double diff, mul, quot, sum;

struct arg_struct {
	double arg1;
	double arg2;
};

void* readNumbers(void * args) {
	char s[10];

	printf("Введите первое число:");
	scanf("%s", s);
	first = atof(s);

	printf("Введите второе число:");
	scanf("%s", s);
	second = atof(s);

	printf("Введите третье число:");
	scanf("%s", s);
	third = atof(s);

	printf("\nВведенные числа: %f %f %f", first, second, third);

	pthread_mutex_lock(&mutex);
	FILE *fp = fopen("output.txt", "w+");
	rewind(fp);
	if (fp == NULL)
		printf("\nФайл output.txt не был создан");

	printf("\nReader: Файл output.txt создан.\n");
	fprintf(fp, "%f %f %f", first, second, third);
	fclose(fp);
	pthread_mutex_unlock(&mutex);

	return EXIT_SUCCESS;
}

void* createReaderThread() {
	pthread_create(&tid[0], NULL, readNumbers, NULL);

	return EXIT_SUCCESS;
}

void* writeForPlus(void* args) {
	pthread_mutex_lock(&plusM);
	FILE *fp = fopen("plus.txt", "w+");

	if (fp == NULL) {
		printf("\nWriter: Файл plus.txt не может быть открыт.\n");
	} else {
		printf("\nWriter: Файл plus.txt открыт.\n");
		rewind(fp);
		struct arg_struct *arguments = (struct arg_struct *)args;
		fprintf(fp, "%f %f", arguments->arg1, arguments->arg2);
		printf("Writer: Записаны числа: %f %f", arguments->arg1, arguments->arg2);
		fclose(fp);
		printf("\nWriter: Фйл plus.txt закрыт.\n");
	}

	pthread_mutex_unlock(&plusM);

	return EXIT_SUCCESS;
}

void* plus(void * args) {
	pthread_join(tid[2], NULL);
	pthread_mutex_lock(&plusM);
	FILE *fp = fopen("plus.txt", "r+");

	if (fp == NULL) {
		printf("\nCounter: Файл plus.txt не может быть открыт.\n");
	} else {
		printf("\nCounter: Файл plus.txt открыт.\n");
		double a, b;
		char aa[10], bb[10];

		rewind(fp);
		fscanf(fp, "%s %s", aa, bb);
		a = atof(aa);
		b = atof(bb);
		sum = a + b;
		printf("%f + %f = %f", a, b, sum);
		fclose(fp);
		printf("\nCounter: Файл plus.txt закрыт.\n");
	}

	pthread_mutex_unlock(&plusM);

	return EXIT_SUCCESS;
}

void* writeForMinus(void* args) {
	pthread_mutex_lock(&minusM);
	FILE *fp = fopen("minus.txt", "w+");

	if (fp == NULL) {
		printf("\nWriter: Файл minus.txt не может быть открыт.\n");
	} else {
		printf("\nWriter: Файл minus.txt открыт.\n");
		rewind(fp);
		struct arg_struct *arguments = (struct arg_struct *)args;
		fprintf(fp, "%f %f", arguments->arg1, arguments->arg2);
		printf("Записаны числа: %f %f", arguments->arg1, arguments->arg2);
		fclose(fp);
		printf("\nWriter: Файл minus.txt закрыт.\n");
	}
	pthread_mutex_unlock(&minusM);

	return EXIT_SUCCESS;
}

void* minus(void * args) {
	pthread_join(tid[4], NULL);
	pthread_mutex_lock(&minusM);
	FILE *fp = fopen("minus.txt", "r+");

	if (fp == NULL) {
		printf("\nCounter: Файл minus.txt не может быть открыт.\n");
	} else {
		printf("\nCounter: Файл minus.txt открыт.\n");
		double a, b;
		char aa[10], bb[10];

		rewind(fp);
		fscanf(fp, "%s %s", aa, bb);
		a = atof(aa);
		b = atof(bb);
		diff = a - b;
		printf("%f - %f = %f", a, b, diff);
		fclose(fp);
		printf("\nCounter: Файл minus.txt закрыт.\n");
	}

	pthread_mutex_unlock(&minusM);

	return EXIT_SUCCESS;
}

void* writeForMul(void* args) {
	pthread_mutex_lock(&mulM);
	FILE *fp = fopen("mul.txt", "w+");

	if (fp == NULL) {
		printf("\nWriter: Файл mul.txt не может быть открыт.\n");
	} else {
		printf("\nWriter: Файл mul.txt открыт.\n");
		rewind(fp);
		struct arg_struct *arguments = (struct arg_struct *)args;
		fprintf(fp, "%f %f", arguments->arg1, arguments->arg2);
		printf("Записаны числа: %f %f", arguments->arg1, arguments->arg2);
		fclose(fp);
		printf("\nWriter: Файл mul.txt закрыт.\n");
	}

	pthread_mutex_unlock(&mulM);

	return EXIT_SUCCESS;
}

void* multiple(void* args) {
	pthread_join(tid[6], NULL);
	pthread_mutex_lock(&mulM);
	FILE *fp = fopen("mul.txt", "r+");

	if (fp == NULL) {
		printf("\nCounter: Файл mul.txt не может быть открыт.\n");
	} else {
		printf("\nCounter: Файл mul.txt открыт.\n");
		double a, b;
		char aa[10], bb[10];

		rewind(fp);
		fscanf(fp, "%s %s", aa, bb);
		a = atof(aa);
		b = atof(bb);
		mul = a * b;
		printf("%f * %f = %f", a, b, mul);
		fclose(fp);
		printf("\nCounter: Файл mul.txt закрыт.\n");
	}

	pthread_mutex_unlock(&mulM);

	return EXIT_SUCCESS;
}

void* writeForQuot(void* args) {
	pthread_mutex_lock(&quotM);
	FILE *fp = fopen("quot.txt", "w+");

	if (fp == NULL) {
		printf("\nWriter: Файл quot.txt не может быть открыт.\n");
	} else {
		printf("\nWriter: Файл quot.txt открыт.\n");
		rewind(fp);
		struct arg_struct *arguments = (struct arg_struct *)args;
		fprintf(fp, "%f %f", arguments->arg1, arguments->arg2);
		printf("Записаны числа: %f %f", arguments->arg1, arguments->arg2);
		fclose(fp);
		printf("\nWriter: Файл quot.txt закрыт.\n");
	}

	pthread_mutex_unlock(&quotM);

	return EXIT_SUCCESS;
}

void* quotate(void* args) {
	pthread_join(tid[8], NULL);
	pthread_mutex_lock(&quotM);
	FILE *fp = fopen("quot.txt", "r+");

	if (fp == NULL) {
		printf("\nCounter: Файл quot.txt не может быть открыт.\n");
	} else {
		printf("\nCounter: Файл quot.txt открыт.\n");
		double a, b;
		char aa[10], bb[10];

		rewind(fp);
		fscanf(fp, "%s %s", aa, bb);
		a = atof(aa);
		b = atof(bb);
		quot = a / b;
		printf("%f / %f = %f", a, b, quot);
		fclose(fp);
		printf("\nCounter: Файл quot.txt закрыт.\n");
	}

	pthread_mutex_unlock(&quotM);

	return EXIT_SUCCESS;
}

double countMx(double params[], int numOfParams) {
	struct arg_struct arguments = { .arg1 = 0.0, .arg2 = 0.0 };
	double count = 0.0;
	for (int i = 0; i < numOfParams; i++) {
		arguments.arg1 = count;
		arguments.arg2 = params[i];
		pthread_create(&tid[2], NULL, writeForPlus, (void *)&arguments);
		pthread_create(&tid[3], NULL, plus, NULL);
		pthread_join(tid[3], NULL);
		count = sum;
	}
	return count / numOfParams;
}

double count(double params[], int numOfParams) {
	struct arg_struct arguments = { .arg1 = 0.0, .arg2 = 0.0 };
	double disp = 0.0;
	double mx = countMx(params, numOfParams);

	for (int i = 0; i < numOfParams; i++) {
		arguments.arg1 = params[i];
		arguments.arg2 = mx;
		pthread_create(&tid[4], NULL, writeForMinus, (void *)&arguments);
		pthread_create(&tid[5], NULL, minus, NULL);
		pthread_join(tid[5], NULL);

		arguments.arg1 = diff;
		arguments.arg2 = diff;
		pthread_create(&tid[6], NULL, writeForMul, (void *)&arguments);
		pthread_create(&tid[7], NULL, multiple, NULL);
		pthread_join(tid[7], NULL);

		arguments.arg1 = mul;
		arguments.arg2 = 2;
		pthread_create(&tid[8], NULL, writeForQuot, (void *)&arguments);
		pthread_create(&tid[9], NULL, quotate, NULL);
		pthread_join(tid[9], NULL);
		disp += quot;
	}

	return disp;
}

void* countDispersion(void* args) {
	double a, b, c;
	pthread_join(tid[0], NULL);
	pthread_mutex_lock(&mutex);
	FILE *fp = fopen("output.txt", "r+");

	if (fp == NULL) {
		printf("\nCounter thread: Файл output.txt не может быть открыт.");
	} else {
		printf("\nCounter thread: Файл output.txt открыт.\n");
		rewind(fp);

		char aa[10], bb[10], cc[10];
		fscanf(fp, "%s %s %s", aa, bb, cc);
		printf("%s %s %s", aa, bb, cc);
		a = atof(aa);
		b = atof(bb);
		c = atof(cc);
		printf("\nЗаписаны числа: %f %f %f\n", a, b, c);
		double mas[] = { a, b, c };
		dispersion = count(mas, 3);

		fprintf(fp, "\n%f", dispersion);
		fclose(fp);
	}

	pthread_mutex_unlock(&mutex);

	return EXIT_SUCCESS;
}

void* createCounterThread() {
	pthread_create(&tid[1], NULL, countDispersion, NULL);

	return EXIT_SUCCESS;
}

void* createMutex() {
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&plusM, NULL);
	pthread_mutex_init(&minusM, NULL);
	pthread_mutex_init(&mulM, NULL);
	pthread_mutex_init(&quotM, NULL);

	return EXIT_SUCCESS;
}

int main() {
	printf("\n\nПрограмма вычисления выборочной дисперсии 3-х чисел\n\n");

	createMutex();
	createReaderThread();
	createCounterThread();
	pthread_join(tid[1], NULL);

	printf("\nMain thread. Дисперсия = %f", dispersion);

	return EXIT_SUCCESS;;
}
