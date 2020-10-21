#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "school.h"
#include "student.h"
#define START_ID 20180000
/*
학생관리: 학생 파일 사용, 학생 등록(이름, 전화번호, 주소, 주민번호, 
학번(생성), 소속학과 정보, 이메일 포함 및 추가 정보 등), 
학생 정보 검색(이름/전화번호/생년월일) 및 
수정(등록/휴학/졸업/자퇴 등 상태, 입학일/졸업일/휴학일/자퇴일, 
수강과목 및 학점, 장학금 내용 및 금액 정보 포함 및 추가 정보 등)
*/

int student(char* fileName) {
	int num;

	while (1) { // 무한 반복
		printf("번호를 입력하세요.\n1. 학생 등록\n2. 학생 정보 검색\n");
		printf("3. 학생 정보 수정\n9. 처음 페이지로\n>> ");

		scanf("%d", &num); getchar();

		switch (num) {
		case 1:
			regist(fileName);
			break;
		case 2:
			query(fileName);
			break;
		case 3:
			update(fileName);
			break;
		case 8:
			print(fileName);
			break;
		case 9:
			return 1;
		default:
			printf("* 잘못된 번호!\n");
			break;
		}
		rewind(stdin); // 만약의 버퍼 정리
	}

	return 1;
}

// 학생 등록
int regist(char* fileName) {
	printf("** 학생 등록 ** \n");

	struct student rec = { 0 };
	struct student cmp = { 0 };
	FILE* fp;

	// rb 옵션으로 파일이 존재하는지 확인
	fp = fopen(fileName, "rb");

	// 파일이 존재하지 않는다면 fp가 NULL일 것이고 wb+ 옵션으로 파일을 새로 작성한다.
	if (fp == NULL)
		fp = fopen(fileName, "wb+");
	// fp가 NULL이 아니면 파일이 존재하기 때문에 fclose로 닫고 rb+ 옵션으로 다시 불러온다
	else {
		fclose(fp);
		fp = fopen(fileName, "rb+");
		/* rb+ 옵션으로 여는 이유
		ab rb로 파일을 열연 fseek가 무시되어 fwrite로 원하는 곳에 데이터를 저장할 수 없음
		ab+ 옵션으로도 가능하다고는 하지만 rb+만 정상 작동
		*/
	}

	// 시작 학번 표시
	printf("START number is %d\n", START_ID);

	while (1) {
		printf("%6s %6s %6s %6s %6s %6s\n", "학번", "이름", "전화번호", "주소", "주민번호", /*"소속학과", */"이메일");
		scanf("%d %s %s %s %s %s", &rec.id, rec.name, rec.hp, rec.address, rec.personNum, rec.email);
		// 입력한 위치로 이동
		fseek(fp, (rec.id - START_ID) * sizeof(rec), SEEK_SET);

		if ((fread(&cmp, sizeof(cmp), 1, fp) > 0)) {
			if (rec.id == cmp.id) {
				printf("이미 존재하는 번호\n");
				continue;
			}
			else {
				rec.state = 1;
				fseek(fp, -sizeof(rec), SEEK_CUR);
				fwrite(&rec, sizeof(rec), 1, fp);
			}
		}	// 데이터 읽기에 실패한 경우 그냥 fwrite 수행
		else fwrite(&rec, sizeof(rec), 1, fp);

		char yn;
		printf("Continue? >> ");
		scanf(" %c", &yn); getchar();
		if (yn == 'Y' || yn == 'y') continue;
		else break;
	}

	rewind(stdin);
	fclose(fp);
	return 1;
}

int query(char* fileName) {
	printf("** 학생 정보 검색 ** \n");
	int id;

	struct student rec = { 0 };
	FILE* fp;

	fp = fopen(fileName, "r");

	while (1) {
		printf("검색할 학생의 학번 : ");

		if (scanf("%d", &id) == 1) {
			fseek(fp, (id - START_ID) * sizeof(rec), SEEK_SET);

			if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) {
				printf("%4s %3s %4s %4s %4s %4s\n", "학번", "이름", "전화번호", "주소", "주민번호", /*"소속학과", */"이메일");
				printf("학번: %d\t이름: %s\t전화번호: %s\n주소: %s\n주민번호: %s\t이메일: %s\n", rec.id, rec.name, rec.hp, rec.address, rec.personNum, rec.email);
			}
			else printf("%d 학번의 학생이 없습니다.\n", id);
		}
		else printf("입력 오류\n");
		getchar();
	}

	rewind(stdin);
	fclose(fp);

	return 1;
}

int update(char* fileName) {
	printf("** 학생 정보 수정 ** \n");

	return 1;

}

int print(char* fileName) {
	printf("** 학생 정보 출력 (띠버깅) ** \n");

	struct student rec = { 0 };
	FILE* fp;

	fp = fopen(fileName, "r");

	while (fread(&rec, sizeof(rec), 1, fp) > 0)
	{
		if (rec.id != 0) {
			printf("학번: %d\t이름: %s\t전화번호: %s\n주소: %s\n주민번호: %s\t이메일: %s\n", rec.id, rec.name, rec.hp, rec.address, rec.personNum, rec.email);
			printf("상태: %s", );
		}
	}

	fclose(fp);

	
	return 1;
}