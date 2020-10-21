// 학생 헤더
struct student {
	int id; // 학번
	char name[20]; // 학생 이름
	char hp[12]; // 휴대폰 번호
	char personNum[12]; // 주민번호 13자리
	
	char email[100]; // 이메일
	char address[100]; // 주소

	int a; // 대학
	int b; // 학과
	
	int state; // 상태 등록, 휴학, 졸업, 자퇴
	int date[3]; // 입학[0], 휴학[1], 졸업[2], 자퇴일[3]
	
	int grade[14]; // 학기별 신청 학점 1년 2 * 7 (건축 5 + 초과학기 가능성 2년) 
	/*
	struct scholarship jh[20]; // 장학금 목록은 20개 까지만
	struct classInfo sg[12]; // 최대 수강 가능 수업 12개 
	*/
};

// 장학금
struct scholarship {
	char name[20]; // 장학금 이름
	int sum; // 지급 금액
};

// 수강 정보
struct classInfo {
	char name[20]; // 과목명
	int grade; // 학점
};

int regist(char* fileName);
int query(char* fileName);
int update(char* fileName);
// int del(); 삭제는 구현 던질까 말까
int print(char* fileName); // 전부 출력은 디버깅 할때만 해도 될 듯