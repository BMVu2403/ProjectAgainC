// mk và tk là 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct student{
    char studentId[10];
    char classroomId[10];
    char name[20];
    char email[30];
    char phone[20];
    char password[20];
};

struct classroom{
    char nameClass[10];
    char idTeacher[10];
    char idClass[10];
    struct student students[];
};

struct teacher{
    char idTeacher[10];
    char idClassroom[10];
    char nameTeacher[20];
    char email[30];
    char phone[20];
    struct classroom classrooms[];
};

void loadStudents(struct student students[], int *size, FILE *file);
void saveStudents(struct student students[], int size, FILE *file);
void printStudents(struct student students[], int size);
void addStudent(struct student students[], int *size, FILE *file);
void updateStudent(struct student students[], int size);
void deleteStudent(struct student students[],int *size, FILE *file);
void sortStudent(struct student students[], int size);
void searchNameStudent(struct student students[], int size);

void loadTeachers(struct teacher teachers[], int *sizeGV, FILE *file);
void saveTeachers(struct teacher teachers[], int sizeGV, FILE *file);
void printTeachers(struct teacher teachers[], int sizeGV);
void addTeacher(struct teacher teachers[], int *sizeGV, FILE *file);
void updateTeacher(struct teacher teachers[], int sizeGV);
void deleteTeacher(struct teacher teachers[],int *sizeGV, FILE *fileTeacher);
void searchNameTeacher(struct teacher teachers[], int sizeGV);

void loadClassrooms(struct classroom classrooms[], int *sizeCL, FILE *fileCL);
void saveClassrooms(struct classroom classrooms[], int sizeCL, FILE *fileCL);
void addClassroom(struct classroom classrooms[], int *sizeCL, struct teacher teachers[], int sizeGV);
void printClassrooms(struct classroom classrooms[], int sizeCL);
void updateClassroom(struct classroom classrooms[], int sizeCL);
void deleteClassroom(struct classroom classrooms[], int *sizeCL);


void loadStudents(struct student students[], int *size, FILE *file){
    file = fopen("students.bin", "rb");
    if(file == NULL){
        *size = 0;
        return;
    }
    if(fread(size, sizeof(int), 1, file) != 1){
        *size = 0;
    }
    if(*size > 0){
        if (fread(students, sizeof(struct student), *size, file) != *size){
            *size = 0;
        }
    }
    fclose(file);
}

void saveStudents(struct student students[], int size, FILE *file){
    file = fopen("students.bin", "wb");
    if(file == NULL){
        printf("Khong the mo file de ghi!\n");
        return;
    }
    fwrite(&size, sizeof(int), 1, file);
    fwrite(students, sizeof(struct student), size, file);
    fclose(file);
}

void printStudents(struct student students[], int size){
    if(size == 0){
        printf("Danh sach sinh vien rong!\n");
        return;
    }
    printf("Danh sach sinh vien:\n");
    printf("\t\t\t***All students ***\n");
    printf("|==========|====================|==============================|===============|\n");
    printf("|%-10s|%-20s|%-30s|%-15s|\n","    ID","        Name","             Gmail","  Phone   ");
    printf("|==========|====================|==============================|===============|\n");
    for (int i = 0; i < size; i++) {
        printf("|%-10s|%-20s|%-30s|%-15s|\n", students[i].studentId, students[i].name, students[i].email, students[i].phone);
        printf("|----------|--------------------|------------------------------|---------------|\n");
    }
}

int checkIdStudent(struct student students[], int size, char *id){
    for(int i = 0; i < size; i++){
        if(strcmp(students[i].studentId, id) == 0){
            return 1;
        }
    }
    return 0;
}

void addStudent(struct student students[], int *size, FILE *file){
    if(*size >= 100){
        printf("Danh sach sinh vien da day!\n");
        return;
    }
    struct student newStudent;
    int flag = 0;
    do{
        printf("Nhap ID sinh vien: ");
        fgets(newStudent.studentId, sizeof(newStudent.studentId), stdin);
        newStudent.studentId[strcspn(newStudent.studentId, "\n")] = '\0';
        if(strlen(newStudent.studentId) == 0){
            printf("ID khong duoc trong\n");
            flag = 0; 
        }else if (checkIdStudent(students, *size, newStudent.studentId)) {
            printf("ID da ton tai, nhap ID khac.\n");
            flag = 0;
        }else{
            flag = 1;
        }
    }while(!flag);
    do {
        printf("Nhap Ten sinh vien: ");
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
        if(strlen(newStudent.name) == 0){
            printf("Ten khong duoc trong\n");
            flag = 0;
        }else{
            flag = 1;
        }
    }while(!flag);
    do {
        printf("Nhap Email sinh vien: ");
        fgets(newStudent.email, sizeof(newStudent.email), stdin);
        newStudent.email[strcspn(newStudent.email, "\n")] = '\0';
        if(strlen(newStudent.email) == 0){
            printf("Email khong duoc trong\n");
            flag = 0;
        }else{
            flag = 1;
        }
    }while(!flag);
    do{
        printf("Nhap Phone sinh vien: ");
        fgets(newStudent.phone, sizeof(newStudent.phone), stdin);
        newStudent.phone[strcspn(newStudent.phone, "\n")] = '\0';
        if(strlen(newStudent.phone) == 0){
            printf("Phone khong duoc trong\n");
            flag = 0;
        }else{
            flag = 1;
        }
    }while(!flag);
    students[*size] = newStudent;
    (*size)++;
    saveStudents(students, *size, file);
    printf("Them sinh vien thanh cong!\n");
}

void updateStudent(struct student students[], int size){
    char id[10];
    int flag = 0;
    printf("Nhap ID sinh vien muon sua: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    for(int i = 0; i < size; i++){
        if(strcmp(students[i].studentId, id) == 0){
            flag = 1;
            printf("Thong tin sinh vien hien tai:\n");
            printf("ID: %s\n", students[i].studentId);
            printf("Ten: %s\n", students[i].name);
            printf("Email: %s\n", students[i].email);
            printf("Phone: %s\n", students[i].phone);
            printf("Nhap Ten moi: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';
            printf("Nhap Email moi: ");
            fgets(students[i].email, sizeof(students[i].email), stdin);
            students[i].email[strcspn(students[i].email, "\n")] = '\0';
            printf("Nhap Phone moi: ");
            fgets(students[i].phone, sizeof(students[i].phone), stdin);
            students[i].phone[strcspn(students[i].phone, "\n")] = '\0';
            printf("Thong tin sinh vien da duoc cap nhat thanh cong!\n");
            break;
        }
    }
    if(!flag){
        printf("ID sinh vien khong ton tai!\n");
    }
}

void deleteStudent(struct student students[],int *size, FILE *file){
    char id[10];
    int flag = 0;
    printf("Nhap ID sinh vien muon xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    for(int i = 0; i < *size; i++){
        if(strcmp(students[i].studentId, id) == 0){
            flag = 1;
            printf("Thong tin sinh vien tim thay:\n");
            printf("ID: %s\n", students[i].studentId);
            printf("Ten: %s\n", students[i].name);
            printf("Email: %s\n", students[i].email);
            printf("Phone: %s\n", students[i].phone);
            char xacNhan;
            printf("Ban muon xoa sinh vien nay?(Y/N): ");
            scanf(" %c", &xacNhan);
            getchar();
            if(xacNhan == 'Y' || xacNhan == 'y'){
                for(int j = i; j < *size - 1; j++){
                    students[j] = students[j + 1];
                }
                (*size)--;
                saveStudents(students, *size, file);
                printf("Xoa sinh vien thanh cong!\n");
            }else{
                printf("Huy xoa sinh vien.\n");
            }
            break;
        }
    }
    if(!flag){
        printf("Khong tim duoc sinh vien.\n");
    }
}

void sortStudent(struct student students[], int size){
    int choiceSort;
    struct student temp;
    printf("\t\t\t\t\t  ** Edit All Students ****\n");
    printf("\t\t\t\t\t1. Sap xep tu A den Z\n");
    printf("\t\t\t\t\t2. Sap xep tu Z den A\n");
    printf("\t\t\t\t\tLua chon cua ban: ");
    scanf("%d", &choiceSort);
    getchar();
    int i = 0, j;
    while(i < size - 1){
        j=i+1;
        while(j < size){
            const char *lastName1 = strrchr(students[i].name, ' ');
            const char *lastName2 = strrchr(students[j].name, ' ');
            lastName1 = (lastName1) ? lastName1 + 1 : students[i].name;
            lastName2 = (lastName2) ? lastName2 + 1 : students[j].name;
            if((choiceSort == 1 && strcmp(lastName1, lastName2) > 0) || (choiceSort == 2 && strcmp(lastName1, lastName2) < 0)){
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
            j++;
        }
        i++;
    }
    printf("Sap xep sinh vien thanh cong theo ten cuoi!!!\n");
}

void searchNameStudent(struct student students[], int size){
    char searchName[30];
    int flag = 0;
    printf("Nhap ten sinh vien muon tim kiem: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    printf("\nTim thay sinh vien ten: %s\n", searchName);
    printf("|==========|====================|==============================|===============|\n");
    printf("|%-10s|%-20s|%-30s|%-15s|\n", "    ID", "        Name", "             Gmail", "  Phone   ");
    printf("|==========|====================|==============================|===============|\n");
    for(int i = 0; i < size; i++){
        if(strstr(students[i].name, searchName)){
            printf("|%-10s|%-20s|%-30s|%-15s|\n", students[i].studentId, students[i].name, students[i].email, students[i].phone);
            printf("|----------|--------------------|------------------------------|---------------|\n");
            flag = 1;
        }
    }
    if(!flag){
        printf("Khong tim thay sinh vien nao!\n");
    }
}
void loadTeachers(struct teacher teachers[], int *sizeGV, FILE *fileTeacher){
    fileTeacher = fopen("teacher.bin", "rb");
    if(fileTeacher == NULL){
        *sizeGV = 0;
        return;
    }
    if(fread(sizeGV, sizeof(int), 1, fileTeacher) != 1){
        *sizeGV = 0;
    }
    if(*sizeGV > 0){
        if (fread(teachers, sizeof(struct teacher), *sizeGV, fileTeacher) != *sizeGV){
            *sizeGV = 0;
        }
    }
    fclose(fileTeacher);
}

void saveTeachers(struct teacher teachers[], int sizeGV, FILE *fileTeacher){
    fileTeacher = fopen("teacher.bin", "wb");
    if(fileTeacher == NULL){
        printf("Khong the mo file de ghi!\n");
        return;
    }
    fwrite(&sizeGV, sizeof(int), 1, fileTeacher);
    fwrite(teachers, sizeof(struct teacher), sizeGV, fileTeacher);
    fclose(fileTeacher);
}

void printTeachers(struct teacher teachers[], int sizeGV){
    if(sizeGV == 0){
        printf("Danh sach giao vien rong!\n");
        return;
    }
    printf("Danh sach giao vien:\n");
    printf("\t\t\t***ALL TEACHERS ***\n");
    printf("|==========|====================|==============================|===============|\n");
    printf("|%-10s|%-20s|%-30s|%-15s|\n","    ID","        Name","             Gmail","  Phone   ");
    printf("|==========|====================|==============================|===============|\n");
    for (int i = 0; i < sizeGV; i++) {
        printf("|%-10s|%-20s|%-30s|%-15s|\n", teachers[i].idTeacher, teachers[i].nameTeacher, teachers[i].email, teachers[i].phone);
        printf("|----------|--------------------|------------------------------|---------------|\n");
    }
}

int checkIdTeacher(struct teacher teachers[], int sizeGV, char *id){
    for(int i = 0; i < sizeGV; i++){
        if(strcmp(teachers[i].idTeacher, id) == 0){
            return 1;
        }
    }
    return 0;
}

void addTeacher(struct teacher teachers[], int *sizeGV, FILE *fileTeacher){
    if(*sizeGV >= 100){
        printf("Danh sach giao vien da day!\n");
        return;
    }
    struct teacher newTeacher;
    int flag = 0;
    do{
        printf("Nhap ID giao vien: ");
        fgets(newTeacher.idTeacher, sizeof(newTeacher.idTeacher), stdin);
        newTeacher.idTeacher[strcspn(newTeacher.idTeacher, "\n")] = '\0';
        if(strlen(newTeacher.idTeacher) == 0){
            printf("ID khong duoc trong\n");
            flag = 0; 
        }else if(checkIdTeacher(teachers, *sizeGV, newTeacher.idTeacher)){
            printf("ID da ton tai, nhap ID khac.\n");
            flag = 0;
        }else{
            flag = 1;
        }
    }while(!flag);
    do{
        printf("Nhap Ten giao vien: ");
        fgets(newTeacher.nameTeacher, sizeof(newTeacher.nameTeacher), stdin);
        newTeacher.nameTeacher[strcspn(newTeacher.nameTeacher, "\n")] = '\0';
        if(strlen(newTeacher.nameTeacher) == 0){
            printf("Ten khong duoc trong\n");
            flag = 0;
        }else{
            flag = 1;
        }
    }while(!flag);
    do {
        printf("Nhap Email giao vien: ");
        fgets(newTeacher.email, sizeof(newTeacher.email), stdin);
        newTeacher.email[strcspn(newTeacher.email, "\n")] = '\0';
        if(strlen(newTeacher.email) == 0){
            printf("Email khong duoc trong\n");
            flag = 0;
        }else{
            flag = 1;
        }
    }while(!flag);
    do{
        printf("Nhap Phone giao vien: ");
        fgets(newTeacher.phone, sizeof(newTeacher.phone), stdin);
        newTeacher.phone[strcspn(newTeacher.phone, "\n")] = '\0';
        if(strlen(newTeacher.phone) == 0){
            printf("Phone khong duoc trong\n");
            flag = 0;
        }else{
            flag = 1;
        }
    }while(!flag);
    
    teachers[*sizeGV] = newTeacher;
    (*sizeGV)++;
    saveTeachers(teachers, *sizeGV, fileTeacher);
    printf("Them giao vien thanh cong\n");
}

void updateTeacher(struct teacher teachers[], int sizeGV){
    char id[10];
    int flag = 0;
    printf("Nhap ID giao vien muon sua: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    for(int i = 0; i < sizeGV; i++){
        if(strcmp(teachers[i].idTeacher, id) == 0){
            flag = 1;
            printf("Thong tin giao vien hien tai:\n");
            printf("ID: %s\n",teachers[i].idTeacher);
            printf("Ten: %s\n",teachers[i].nameTeacher);
            printf("Email: %s\n",teachers[i].email);
            printf("Phone: %s\n",teachers[i].phone);
            printf("Nhap Ten moi: ");
            fgets(teachers[i].nameTeacher, sizeof(teachers[i].nameTeacher), stdin);
            teachers[i].nameTeacher[strcspn(teachers[i].nameTeacher, "\n")] = '\0';
            printf("Nhap Email moi: ");
            fgets(teachers[i].email, sizeof(teachers[i].email), stdin);
            teachers[i].email[strcspn(teachers[i].email, "\n")] = '\0';
            printf("Nhap Phone moi: ");
            fgets(teachers[i].phone, sizeof(teachers[i].phone), stdin);
            teachers[i].phone[strcspn(teachers[i].phone, "\n")] = '\0';
            printf("Thong tin giao vien cap nhat thanh cong\n");
            break;
        }
    }
    if(!flag){
        printf("ID giao vien khong ton tai\n");
    }
}

void deleteTeacher(struct teacher teachers[],int *sizeGV, FILE *fileTeacher){
    char id[10];
    int flag = 0;
    printf("Nhap ID giao vien muon xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    for(int i = 0; i < *sizeGV; i++){
        if(strcmp(teachers[i].idTeacher, id) == 0){
            flag = 1;
            printf("Thong tin giao vien tim thay:\n");
            printf("ID: %s\n",teachers[i].idTeacher);
            printf("Ten: %s\n",teachers[i].nameTeacher);
            printf("Email: %s\n",teachers[i].email);
            printf("Phone: %s\n",teachers[i].phone);
            char xacNhan;
            printf("Ban muon xoa giao vien nay?(Y/N): ");
            scanf(" %c", &xacNhan);
            getchar();
            if(xacNhan == 'Y' || xacNhan == 'y'){
                for(int j = i; j < *sizeGV - 1; j++){
                    teachers[j] = teachers[j + 1];
                }
                (*sizeGV)--;
                saveTeachers(teachers, *sizeGV, fileTeacher);
                printf("Xoa giao vien thanh cong!\n");
            }else{
                printf("Huy xoa giao vien.\n");
            }
            break;
        }
    }
    if(!flag){
        printf("Khong tim duoc giao vien.\n");
    }
}

void searchNameTeacher(struct teacher teachers[], int sizeGV){
    char searchName[30];
    int flag = 0;
    printf("Nhap ten giao vien muon tim kiem: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    printf("\nTim thay giao vien ten: %s\n", searchName);
    printf("|==========|====================|==============================|===============|\n");
    printf("|%-10s|%-20s|%-30s|%-15s|\n", "    ID", "        Name", "             Gmail", "  Phone   ");
    printf("|==========|====================|==============================|===============|\n");
    for(int i = 0; i < sizeGV; i++){
        if(strstr(teachers[i].nameTeacher, searchName)){
            printf("|%-10s|%-20s|%-30s|%-15s|\n",teachers[i].idTeacher,teachers[i].nameTeacher,teachers[i].email,teachers[i].phone);
            printf("|----------|--------------------|------------------------------|---------------|\n");
            flag = 1;
        }
    }
    if(!flag){
        printf("Khong tim thay giao vien nao!\n");
    }
}

void loadClassrooms(struct classroom classrooms[], int *sizeCL, FILE *fileCL){
    fileCL = fopen("classroom.bin", "rb");
    if (fileCL == NULL) {
        *sizeCL = 0;
        return;
    }
    if(fread(sizeCL, sizeof(int), 1, fileCL) != 1){
        *sizeCL = 0;
    }
    if(*sizeCL > 0){
        if(fread(classrooms, sizeof(struct classroom), *sizeCL, fileCL) != *sizeCL){
            *sizeCL = 0;
        }
    }
    fclose(fileCL);
}

void saveClassrooms(struct classroom classrooms[], int sizeCL, FILE *fileCL){
    fileCL = fopen("classroom.bin", "wb");
    if(fileCL == NULL){
        printf("Khong the mo file de ghi!\n");
        return;
    }
    fwrite(&sizeCL, sizeof(int), 1, fileCL);
    fwrite(classrooms, sizeof(struct classroom), sizeCL, fileCL);
    fclose(fileCL);
}

void addClassroom(struct classroom classrooms[], int *sizeCL, struct teacher teachers[], int sizeGV){
    struct classroom newClass;
    printf("Nhap ID lop: ");
    scanf("%9s", newClass.idClass);
    getchar();
    printf("Nhap ten lop: ");
    scanf("%9s", newClass.nameClass);
    getchar();
    printf("Danh sach giao vien:\n");
    for(int i = 0; i < sizeGV; i++){
        printf("%d. %s - ID: %s\n", i + 1, teachers[i].nameTeacher, teachers[i].idTeacher);
    }
    char teacherID[10];
    int flag = 0;
    while(!flag){
        printf("Nhap ID giao vien: ");
        scanf("%9s", teacherID);
        getchar();
        for(int i = 0; i < sizeGV; i++){
            if(strcmp(teachers[i].idTeacher, teacherID) == 0){
                strcpy(newClass.idTeacher, teacherID);
                flag = 1;
                break;
            }
        }
        if(!flag){
            printf("ID giao vien khong hop le! nhap lai.\n");
        }
    }
    classrooms[*sizeCL] = newClass;
    (*sizeCL)++;
    saveClassrooms(classrooms, *sizeCL, fopen("classroom.bin", "wb"));
    printf("Lop hoc %s da duoc them thanh cong!\n", newClass.nameClass);
}

void printClassrooms(struct classroom classrooms[], int sizeCL){
    printf("\nDanh sach lop hoc:\n");
    printf("====================================================================\n");
    printf("| %-10s | %-15s | %-10s | %-15s |\n", "ID CLASS", "NAME CLASS ", " ID TEACHER  ", " NUMSOFSTUDENTS  ");
    printf("====================================================================\n");
    for(int i = 0; i < sizeCL; i++){
        printf("| %-10s | %-15s | %-10s    | %-15d   |\n", classrooms[i].idClass, classrooms[i].nameClass, classrooms[i].idTeacher, 0);  
        printf("|------------|-----------------|---------------|-------------------|\n");
    }
}

void updateClassroom(struct classroom classrooms[], int sizeCL){
    char idClass[10];
    int flag = 0; 
    printf("Nhap ID lop hoc muon sua: ");
    scanf("%9s", idClass);
    getchar();
    for(int i = 0; i < sizeCL; i++){
        if(strcmp(classrooms[i].idClass, idClass) == 0){
            printf("Thong tin lop hoc hien tai:\n");
            printf("ID: %s, Ten lop: %s, Giao vien: %s\n", classrooms[i].idClass, classrooms[i].nameClass, classrooms[i].idTeacher);
            printf("Nhap ten lop moi: ");
            scanf("%9s", classrooms[i].nameClass);
            getchar();
            printf("Nhap ID giao vien moi: ");
            scanf("%9s", classrooms[i].idTeacher);
            getchar();
            printf("Lop hoc da duoc sua thanh cong\n");
            flag = 1; 
            break;
        }
    }
    if(flag == 0){
        printf("ID lop hoc khong ton tai\n");
    }
}

void deleteClassroom(struct classroom classrooms[], int *sizeCL){
    char idClass[10];
    int flag = 0;  
    printf("Nhap ID lop hoc muon xoa: ");
    scanf("%9s", idClass);
    getchar();
    for(int i = 0; i < *sizeCL; i++){
        if(strcmp(classrooms[i].idClass, idClass) == 0){
            printf("Ban co chac chan muon xoa lop hoc %s (Y/N) ", classrooms[i].nameClass);
            char choice;
            scanf("%c", &choice);
            getchar();
            if(choice == 'Y' || choice == 'y'){
                for(int j = i; j < *sizeCL - 1; j++){
                    classrooms[j] = classrooms[j + 1];
                }
                (*sizeCL)--; 
                printf("Lop hoc da duoc xoa thanh cong!\n");
            }else{
                printf("Hanh dong xoa bi huy\n");
            }
            flag = 1; 
            break;
        }
    }
    if(flag == 0){
        printf("ID lop hoc khong ton tai\n");
    }
}
int main(int argc, char *argv[]){
    struct student students[100];
    struct teacher teachers[100];
    struct classroom classrooms[10];
    int size = 0;
    int sizeGV = 0;
    int sizeCL = 0;
    int choose;
    FILE *file = fopen("students.bin", "rb");
    loadStudents(students, &size, file);
    FILE *fileTeacher = fopen("teacher.bin", "rb");
    loadTeachers(teachers, &sizeGV, fileTeacher);
    FILE *fileCL = fopen("classroom.bin", "rb");
    loadClassrooms(classrooms, &sizeCL, fileCL);
    char email[50];
    char passWord[20];
    do{
        printf("\n\t\t\t\t\t\t1.Login Admin\n");
        printf("\t\t\t\t\t\t2.Thoat!!!\n");
        printf("\t\t\t\t\t\tLua chon cua ban: ");
        scanf("%d",&choose);
        getchar();
        switch(choose){
            case 1:
                do{
                    printf("\n\t\t\t\t\t\t***LOGIN***");
                    printf("\n\t\t\t\t\t\tNhap email: ");
                    fgets(email,sizeof(email),stdin);
                    email[strcspn(email, "\n")] = '\0';
                    printf("\t\t\t\t\t\tNhap password: ");
                    fgets(passWord,sizeof(passWord),stdin);
                    passWord[strcspn(passWord, "\n")] = '\0';
                    if(strcmp(email,"1") == 0 && strcmp(passWord,"1") == 0){
                        printf("\t\t\t\t\t\tDang nhap thanh cong!!!\n");
                    }else{
                        printf("\n\t\t\t\t\t\tSai mk hoac tk, vui long dang nhap lai!!!");
                        continue;
                    }
                    printf("\n\t\t\t\t\t\t***ADMIN***\n");
                    printf("\t\t\t\t\t\t1.QUAN LI SINH VIEN\n");
                    printf("\t\t\t\t\t\t2.QUAN LI LOP HOC\n");
                    printf("\t\t\t\t\t\t3.QUAN LI GIAO VIEN\n");
                    printf("\t\t\t\t\t\t4.THOAT!!!\n");
                    printf("\t\t\t\t\t\tlua chon cua ban: ");
                    scanf("%d",&choose);
                    getchar();
                    switch(choose){
                        case 1:
                            do{
                                printf("\n\t\t\t\t\t***Student Management System Using C***\n");
                                printf("\t\t\t\t\t\tSTUDENT MENU\n");
                                printf("\t\t\t\t\t========================\n");
                                printf("\t\t\t\t\t[1] In danh sach sinh vien.\n");
                                printf("\t\t\t\t\t[2] Them sinh vien.\n");
                                printf("\t\t\t\t\t[3] Sua sinh vien.\n");
                                printf("\t\t\t\t\t[4] Xoa sinh vien.\n");
                                printf("\t\t\t\t\t[5] Tim kiem sinh vien theo ten.\n");
                                printf("\t\t\t\t\t[6] Sap xep danh sach sinh vien theo ten.\n");
                                printf("\t\t\t\t\t[0] Thoat chuong trinh!!!.\n");
                                printf("\t\t\t\t\t========================\n");
                                printf("\t\t\t\t\tLua chon cua ban: ");
                                scanf("%d",&choose);
                                getchar(); 
                                switch(choose){
                                    case 1: printStudents(students, size); break;
                                    case 2: addStudent(students, &size, file); break;
                                    case 3: updateStudent(students, size); break;
                                    case 4: deleteStudent(students, &size, file); break;
                                    case 5: searchNameStudent(students, size); break;
                                    case 6: sortStudent(students, size); break;
                                }
                            }while(choose!=0);
                            break;
                        case 2:
                            do{
                                printf("\n\t\t\t\t\t***Class Management System Using C***");
                                printf("\n\t\t\t\t\t\tCLASS MENU\n");
                                printf("\t\t\t\t\t========================\n");
                                printf("\t\t\t\t\t[1] In danh sach lop hoc.\n");
                                printf("\t\t\t\t\t[2] Them lop hoc.\n");
                                printf("\t\t\t\t\t[3] Sua thong tin lop hoc.\n");
                                printf("\t\t\t\t\t[4] Xoa lop hoc.\n");
                                printf("\t\t\t\t\t[0] Thoat chuong trinh!!!.\n");
                                printf("\t\t\t\t\t========================\n");
                                printf("\t\t\t\t\tLua chon cua ban: ");
                                scanf("%d",&choose);
                                getchar();
                                switch(choose){
                                    case 1: printClassrooms(classrooms, sizeCL); break;
                                    case 2: addClassroom(classrooms, &sizeCL, teachers, sizeGV); break;
                                    case 3: updateClassroom(classrooms, sizeCL); break;
                                    case 4: deleteClassroom(classrooms, &sizeCL); break;
                                }
                            }while(choose!=0);
                            break;
                        case 3:
                            do{
                                printf("\n\t\t\t\t\t***Teacher Management System Using C***");
                                printf("\n\t\t\t\t\t\tTEACHER MENU\n");
                                printf("\t\t\t\t\t========================\n");
                                printf("\t\t\t\t\t[1] In danh sach giao vien.\n");
                                printf("\t\t\t\t\t[2] Them giao vien.\n");
                                printf("\t\t\t\t\t[3] Sua thong tin giao vien.\n");
                                printf("\t\t\t\t\t[4] Xoa giao vien.\n");
                                printf("\t\t\t\t\t[5] Tim kiem giao vien theo ten.\n");
                                printf("\t\t\t\t\t[0] Thoat chuong trinh!!!.\n");
                                printf("\t\t\t\t\t========================\n");
                                printf("\t\t\t\t\tLua chon cua ban: ");
                                scanf("%d",&choose);
                                getchar();
                                switch(choose){
                                    case 1: printTeachers(teachers, sizeGV); break;
                                    case 2: addTeacher(teachers, &sizeGV, file); break;
                                    case 3: updateTeacher(teachers, sizeGV); break;
                                    case 4: deleteTeacher(teachers, &sizeGV, fileTeacher); break;
                                    case 5: searchNameTeacher(teachers, sizeGV); break;
                                }
                            }while(choose!=0);
                            break;
                        case 4: break;
                    }
                }while(choose!=4);
                break;
            case 2:
                break;
        }
    }while(choose!=2);
    return 0;
}
