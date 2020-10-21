#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "school.h"

int main() {
	int num;

	// 파일 경로 처리
	char* fileStudent = malloc(sizeof(char) * 50);
	char* fileProf = malloc(sizeof(char) * 50);
	char* fileAssert = malloc(sizeof(char) * 50);
	fileStudent = "./data_student";
	fileProf = "./data_prof";
	fileAssert = "./data_assert";

	system("clear"); // 화면 정리 (제출할 때는 지우기)

	while (1) { // 무한 반복 실행
		printf("번호를 입력하세요.\n1. 학생 관리\n2. 교직원 관리\n3. 자산 관리\n9. 종료\n>> ");
		scanf("%d", &num); getchar(); // 번호를 입력 받고 getchar로 \n 버퍼를 없앤다.

		switch (num) {
		case 1:
			student(fileStudent);
			break;
		case 2:
			prof(fileProf);
			break;
		case 3:
			assert(fileAssert);
			break;
		case 9:
			return 0;
		default:
			printf("* 잘못된 번호!\n");
			break;
		}
		rewind(stdin); // 만약의 버퍼 정리
	}
	return 0;
}