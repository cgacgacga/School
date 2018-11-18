/* Kuzminov Artem, 10-4, 23/01/2017 */

#define Max 50

typedef struct {
  int Day, Month, Year;
} Date;

typedef struct {
  Date Birthday;
  char Surname[30];
  char Name[30];
  char Number[22];
  int Age;
  int Form;
  char Sex;
  char FormDigit;
} Pupil;

int AddPupil(int cur, Pupil *DB);
int Output(int cur, Pupil *DB)
;

int DeleteByNumber(int cur, Pupil *DB, char *Num);
void SortBy(int cur, Pupil *DB, char adj);
