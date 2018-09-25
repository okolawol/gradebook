#include "databaseif.h"

DatabaseIF::DatabaseIF() {
    openDB();
    checkTable();
}

DatabaseIF::~DatabaseIF() {
    db.close();
}

bool DatabaseIF::openDB() {
    // Find QSLite driver: SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");

    #ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("test.db.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    #else
    // Windows
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName("test.db.sqlite");
    #endif

    // Open databasee
    return db.open();
}

//Table initialization for fist launch
void DatabaseIF::checkTable() {
    //check whether there is a table
    QSqlQuery query;
    if (!query.exec("SELECT * FROM Account;")) {
        createAccountTable();
        insertAccount("301140111 studenta 1234");
        insertAccount("111 instructora 1234");
        insertAccount("222 instructorb 1234");
        insertAccount("301140222 taa 1234");
        insertAccount("301140444 tab 1234");
        insertAccount("1 admina 1234");
        insertAccount("301140333 studentb 1234");
        insertAccount("301140555 studentc 1234");
        insertAccount("301140666 studentd 1234");
        insertAccount("301140777 studente 1234");
        insertAccount("301140888 studentf 1234");
        insertAccount("301140999 studentg 1234");
        insertAccount("301141111 studenth 1234");
        insertAccount("301141222 studenti 1234");
        insertAccount("301141333 studentj 1234");
    }
    if (!query.exec("SELECT * FROM User;")) {
        createUserTable();
        insertUser("301140111 A Student sfu.ca student");
        insertUser("111 A Instructor sfu.ca instructor");
        insertUser("222 B Instructor sfu.ca instructor");
        insertUser("301140222 A TA sfu.ca ta");
        insertUser("301140444 B TA sfu.ca ta");
        insertUser("1 A Admin sfu.ca admin");
        insertUser("301140333 B Student sfu.ca student");
        insertUser("301140555 C Student sfu.ca student");
        insertUser("301140666 D Student sfu.ca student");
        insertUser("301140777 E Student sfu.ca student");
        insertUser("301140888 F Student sfu.ca student");
        insertUser("301140999 G Student sfu.ca student");
        insertUser("301141111 H Student sfu.ca student");
        insertUser("301141222 I Student sfu.ca student");
        insertUser("301141333 J Student sfu.ca student");
    }
    if (!query.exec("SELECT * FROM Admin;")) {
        createAdminTable();
        insertAdmin("1");
    }
    if (!query.exec("SELECT * FROM Instructor;")) {
        createInstructorTable();
        insertInstructor("111 AQ111 CS");
        insertInstructor("222 AQ222 CE");
    }
    if (!query.exec("SELECT * FROM TA;")) {
        createTATable();
        insertTA("301140222 AQ222");
        insertTA("301140444 AQ444");
    }
    if (!query.exec("SELECT * FROM Student;")) {
        createStudentTable();
        insertStudent("301140111 CS Computing");
        insertStudent("301140333 CE Computing");
        insertStudent("301140555 EC Accounting");
        insertStudent("301140666 CS Computing");
        insertStudent("301140777 CS Computing");
        insertStudent("301140888 CS Computing");
        insertStudent("301140999 CS Computing");
        insertStudent("301141111 CS Computing");
        insertStudent("301141222 CS Computing");
        insertStudent("301141333 CS Computing");
    }
    if (!query.exec("SELECT * FROM Semester;")) {
        createSemesterTable();
    }
    if (!query.exec("SELECT * FROM Course;")) {
        createCourseTable();
        insertCourse("CMPT212");
        insertCourse("CMPT365");
        insertCourse("IAT100");
        insertCourse("CMPT100");
        insertCourse("CMPT300");
        insertCourse("CMPT471");
        insertCourse("IAT102");
        insertCourse("MACM101");
        insertCourse("MACM201");
        insertCourse("MACM301");
        insertCourse("CHEM110");
        insertCourse("CHEM120");
    }
    if (!query.exec("SELECT * FROM Class;")) {
        createClassTable();
    }
    if (!query.exec("SELECT * FROM ClassInformation;")) {
        createClassInformationTable();
    }
    if (!query.exec("SELECT * FROM Activity;")) {
        createActivityTable();
    }
    if (!query.exec("SELECT * FROM Grade;")) {
        createGradeTable();
    }
    if (!query.exec("SELECT * FROM LetterGradeRange;")) {
        createLetterGradeRangeTable();
    }

}

/*
 *=========================================================
 *Create Table
 *=========================================================
 */
bool DatabaseIF::createAccountTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE Account "
                         "(id TEXT PRIMARY KEY, "
                         "userName TEXT UNIQUE, "
                         "password TEXT)");
    }
    return res;
}
bool DatabaseIF::createUserTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE User "
                         "(id TEXT PRIMARY KEY, "
                         "firstName TEXT NOT NULL, "
                         "lastName TEXT NOT NULL, "
                         "email TEXT, "
                         "type TEXT)");
    }
    return res;
}

bool DatabaseIF::createAdminTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE Admin "
                         "(id TEXT PRIMARY KEY)");
    }
    return res;
}

bool DatabaseIF::createInstructorTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE Instructor "
                         "(id TEXT PRIMARY KEY, "
                         "office TEXT, "
                         "department TEXT)");
    }
    return res;
}

bool DatabaseIF::createTATable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE TA "
                         "(id TEXT PRIMARY KEY, "
                         "office TEXT)");
    }
    return res;
}

bool DatabaseIF::createStudentTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE Student "
                         "(id TEXT PRIMARY KEY, "
                         "department TEXT, "
                         "major TEXT)");
    }
    return res;
}

bool DatabaseIF::createSemesterTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE Semester "
                         "(semesterId INTEGER PRIMARY KEY, "
                         "year INTEGER, "
                         "term TEXT)");
        deleteSemesterTrigger();
    }
    return res;
}

bool DatabaseIF::createCourseTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE Course "
                         "(courseId INTEGER PRIMARY KEY, "
                         "courseName TEXT UNIQUE)");
    }
    return res;
}

bool DatabaseIF::createClassTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE Class "
                         "(classId INTEGER PRIMARY KEY, "
                         "classSection TEXT, "
                         "courseId INTEGER, "
                         "semesterId INTEGER, "
                         "letterGradeReleased BIT DEFAULT 0, "
                         "UNIQUE(classSection, courseId, semesterId))");
        deleteClassTrigger();
    }
    return res;
}

bool DatabaseIF::createClassInformationTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE ClassInformation "
                         "(id TEXT, "
                         "classId INTEGER, "
                         "letterGrade TEXT, "
                         "PRIMARY KEY(id, classId))");
        deleteClassInformationTrigger();
    }
    return res;
}

bool DatabaseIF::createActivityTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE Activity "
                         "(activityId INTEGER PRIMARY KEY, "
                         "classId INTEGER, "
                         "activity TEXT, "
                         "maxMark DOUBLE, "
                         "weight DOUBLE, "
                         "UNIQUE(classId, activity))");
        deleteActivityTrigger();
    }
    return res;
}

bool DatabaseIF::createGradeTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE Grade "
                         "(id TEXT, "
                         "activityId INTEGER, "
                         "mark DOUBLE, "
                         "PRIMARY KEY(id, activityId))");
    }
    return res;
}

bool DatabaseIF::createLetterGradeRangeTable() {
    bool res = false; //return result

    //check db is already open or not
    if (db.isOpen()) {
        QSqlQuery query;
        res = query.exec("CREATE TABLE LetterGradeRange "
                         "(classId INTEGER PRIMARY KEY, "
                         "scale1 DOUBLE, "
                         "scale2 DOUBLE, "
                         "scale3 DOUBLE, "
                         "scale4 DOUBLE, "
                         "scale5 DOUBLE, "
                         "scale6 DOUBLE, "
                         "scale7 DOUBLE, "
                         "scale8 DOUBLE, "
                         "scale9 DOUBLE, "
                         "scale10 DOUBLE, "
                         "scale11 DOUBLE)");
    }
    return res;
}

//wildcard
vector< vector<string> > DatabaseIF::applyQuery(string aQuery) {
    bool res = false;
    vector< vector<string> > vec;
    QSqlQuery query;
    QString str = QString::fromStdString(aQuery);
    if (db.isOpen()) {
        res = query.exec(str);
    }
    if (res) {
        select(query, vec);
    }
    return vec;
}

/*
 *=========================================================
 *Insert
 *=========================================================
 */

//attributes are the value of each attributes divided by a space
//the order of the value should match the table
//E.g., User: id, name, gpa
//attributes = "NULL Jimmy 2.8"
int DatabaseIF::insertAccount(string attributes) {
    int id = -1;
    //read attributes
    QString str =  QString::fromStdString(attributes);
    QStringList sstr = str.split(" ");

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Account (id, userName, password) "
                          "VALUES (?, ?, ?)");
        id = insert(query, sstr);
    }

    return id;
}

//insertAccount(string userName, string password)
//Because other account is from other place, only admin account can be created
int DatabaseIF::insertAccount(string id, string userName, string password) {
    int rid = -1;
    QStringList sstr;
    sstr.append(QString::fromStdString(id));
    sstr.append(QString::fromStdString(userName));
    sstr.append(QString::fromStdString(password));

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Account (id, userName, password) "
                          "VALUES (?, ?, ?)");
        rid = insert(query, sstr);
    }

    return rid;
}

int DatabaseIF::insertUser(string attributes) {
    int id = -1;
    //read attributes
    QString str =  QString::fromStdString(attributes);
    QStringList sstr = str.split(" ");
    sstr[4] = sstr[4].toLower();    //type should be in lower case

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO User (id, firstName, lastName, email, type) "
                          "VALUES (?, ?, ?, ?, ?)");
        id = insert(query, sstr);
    }

    return id;
}
int DatabaseIF::insertAdmin(string attributes) {
    int id = -1;
    //read attributes
    QString str =  QString::fromStdString(attributes);
    QStringList sstr = str.split(" ");

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Admin (id) "
                          "VALUES (?)");
        id = insert(query, sstr);
    }

    return id;
}

int DatabaseIF::insertInstructor(string attributes) {
    int id = -1;
    //read attributes
    QString str =  QString::fromStdString(attributes);
    QStringList sstr = str.split(" ");

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Instructor (id, office, department) "
                          "VALUES (?, ?, ?)");
        id = insert(query, sstr);
    }

    return id;
}

int DatabaseIF::insertTA(string attributes) {
    int id = -1;
    //read attributes
    QString str =  QString::fromStdString(attributes);
    QStringList sstr = str.split(" ");

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO TA (id, office) "
                          "VALUES (?, ?)");
        id = insert(query, sstr);
    }

    return id;
}

int DatabaseIF::insertStudent(string attributes) {
    int id = -1;
    //read attributes
    QString str =  QString::fromStdString(attributes);
    QStringList sstr = str.split(" ");

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Student (id, department, major) "
                          "VALUES (?, ?, ?)");
        id = insert(query, sstr);
    }

    return id;
}

int DatabaseIF::insertSemester(string year, string term) {
    int id = -1;
    QStringList sstr;
    sstr.append("NULL");
    sstr.append(QString::fromStdString(year));
    sstr.append(QString::fromStdString(term));

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Semester (semesterId, year, term) "
                          "VALUES (?, ?, ?)");
        id = insert(query, sstr);
    }

    return id;
}
int DatabaseIF::insertCourse(string courseName) {
    int id = -1;

    QStringList sstr;
    sstr.append("NULL");
    sstr.append(QString::fromStdString(courseName));

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Course (courseId, courseName) "
                          "VALUES (?, ?)");
        id = insert(query, sstr);
    }

    return id;
}

int DatabaseIF::insertClass(string classSection, int courseId, int semesterId) {
    int id = -1;
    QStringList sstr;
    sstr.append("NULL");
    sstr.append(QString::fromStdString(classSection));
    sstr.append(QString("%1").arg(courseId));
    sstr.append(QString("%1").arg(semesterId));

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Class (classId, classSection, courseId, semesterId) "
                          "VALUES (?, ?, ?, ?)");
        id = insert(query, sstr);
    }

    return id;
}

int DatabaseIF::insertClassInformation(string id, int classId, string letterGrade) {
    int rid = -1;
    QStringList sstr;
    sstr.append(QString::fromStdString(id));
    sstr.append(QString("%1").arg(classId));
    sstr.append(QString::fromStdString(letterGrade));

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO ClassInformation (id, classId, letterGrade) "
                          "VALUES (?, ?, ?)");
        rid = insert(query, sstr);
    }

    return rid;
}

int DatabaseIF::insertActivity(int classId, string activity, double maxMark, double weight) {
    int id = -1;
    QStringList sstr;
    sstr.append("NULL");
    sstr.append(QString("%1").arg(classId));
    sstr.append(QString::fromStdString(activity));
    sstr.append(QString("%1").arg(maxMark));
    sstr.append(QString("%1").arg(weight));

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO Activity (activityId, classId, activity, maxMark, weight) "
                          "VALUES (?, ?, ?, ?, ?)");
        id = insert(query, sstr);
    }

    return id;
}

int DatabaseIF::insertGrade(string id, int activityId, double mark) {
    int rid = -1;
    QStringList sstr;
    sstr.append(QString::fromStdString(id));
    sstr.append(QString("%1").arg(activityId));
    if (mark < 0) {
        sstr.append(QString("NULL"));
    }
    else {
        sstr.append(QString("%1").arg(mark));
    }

    if (db.isOpen()) {
        QSqlQuery query;
        query.exec(QString("SELECT * FROM Grade WHERE id='%1' AND activityId=%2").arg(QString::fromStdString(id)).arg(activityId));
        if (query.next()) {
            if (updateGrade(id, activityId, mark)) {
                rid = 0;
            }
            else {
                rid = -1;
            }
        }
        else {
            query.prepare("INSERT INTO Grade (id, activityId, mark) "
                          "VALUES (?, ?, ?)");
            rid = insert(query, sstr);
        }
    }

    return rid;
}

int DatabaseIF::insertLetterGradeRange(int classId, double scale1, double scale2, double scale3, double scale4, double scale5, double scale6, double scale7, double scale8, double scale9, double scale10, double scale11) {
    int id = -1;
    QStringList sstr;
    sstr.append(QString("%1").arg(classId));
    sstr.append(QString("%1").arg(scale1));
    sstr.append(QString("%1").arg(scale2));
    sstr.append(QString("%1").arg(scale3));
    sstr.append(QString("%1").arg(scale4));
    sstr.append(QString("%1").arg(scale5));
    sstr.append(QString("%1").arg(scale6));
    sstr.append(QString("%1").arg(scale7));
    sstr.append(QString("%1").arg(scale8));
    sstr.append(QString("%1").arg(scale9));
    sstr.append(QString("%1").arg(scale10));
    sstr.append(QString("%1").arg(scale11));

    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT INTO LetterGradeRange (classId, scale1, scale2, scale3, scale4, scale5, scale6, scale7, scale8, scale9, scale10, scale11) "
                          "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
        id = insert(query, sstr);
    }

    return id;
}

//local method for general part
int DatabaseIF::insert(QSqlQuery & query, QStringList & sstr) {
    bool res = false;
    int id = -1;
    for (int i = 0; i < sstr.size(); i++) {
        if (sstr[i].toUpper() == "NULL") {
            query.bindValue(i, QVariant());
        }
        else {
            query.bindValue(i, sstr[i]);
        }
    }
    res = query.exec();
    if (res) {
        id = query.lastInsertId().toInt();
    }

    return id;
}

/*
 *=========================================================
 *Select
 *=========================================================
 */

//local method for selection's general part
void DatabaseIF::select(QSqlQuery & query, vector<vector<string> > & res) {
    while (query.next()) {
        vector<string> temp;
        int index = 0;
        while (query.value(index).isValid()){
            temp.push_back(query.value(index).toString().toStdString());
            index++;
        }
        res.push_back(temp);
    }
}

//select account, argument: [id]
/*
 *=========================================================
 *  Two Overload methods
 *=========================================================
 */
//local method
inline void DatabaseIF::buildSelectAccount(QString & str) {
    str = "SELECT * FROM Account ";
}

//selectAccount(string id)
vector< vector<string> > DatabaseIF::selectAccount() {  //get Account table
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;

    buildSelectAccount(str);
    query.exec(str);
    select(query, res);
    return res;
}

vector< vector<string> > DatabaseIF::selectAccount(string id) { //search by id
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;

    buildSelectAccount(str);
    str += QString("WHERE id='%1'").arg(QString::fromStdString(id));
    query.exec(str);
    select(query, res);
    return res;
}


//select User, argument: [type][id][name], returns empty vector if invalid argument or no result
/*
 *=========================================================
 *  Four Overload methods
 *=========================================================
 */
//local method
inline void DatabaseIF::buildSelectUser(userType & type, QString & str) {
    switch (type) {
        case ADMIN: {
            str = "SELECT * FROM User NATURAL JOIN Admin ";
            break;
        }
        case INSTRUCTOR: {
            str = "SELECT * FROM User NATURAL JOIN Instructor ";
            break;
        }
        case T_A_: {
            str = "SELECT * FROM User NATURAL JOIN TA ";
            break;
        }
        case STUDENT: {
            str = "SELECT * FROM User NATURAL JOIN Student ";
            break;
        }
        default: {
            str = "";
            break;
        }
    }
}

vector< vector<string> > DatabaseIF::selectUser() {
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;

    str = "SELECT * FROM User";
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectUser(userType type) {
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectUser(type, str);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectUser(string id) {
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    if (!id.empty()) {
        str = QString("SELECT * FROM User WHERE id='%1'").arg(QString::fromStdString(id));
        query.exec(str);
        select(query, res);
    }
    return res;
}

//special select for login page, argument: userName, password
//************CAUTION: Althogh only one tuple should be returned, for consistent, it still return 2D vector********
vector< vector<string> > DatabaseIF::selectUser(string userName, string password) {
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;

    if (!userName.empty()) {
        str = QString("SELECT * FROM User NATURAL JOIN (SELECT id FROM Account WHERE userName='%1' AND password='%2')").arg(QString::fromStdString(userName)).arg(QString::fromStdString(password));
        query.exec(str);
        select(query, res);
    }
    return res;
}

vector< vector<string> > DatabaseIF::selectUser(userType type, string id) {
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectUser(type, str);

    if (!id.empty()) {
        str += QString("WHERE id='%1'").arg(QString::fromStdString(id));
        query.exec(str);
        select(query, res);
    }
    return res;
}

//selectSemester(int semesterId)
/*
 *=========================================================
 *  Two Overload methods
 *=========================================================
 */
//local method
inline void DatabaseIF::buildSelectSemester(QString & str) {
    str = "SELECT * FROM Semester ";
}

vector< vector<string> > DatabaseIF::selectSemester() {  //get Semester table
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectSemester(str);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectSemester(int semesterId) {   //search
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectSemester(str);
    str += QString("WHERE semesterId=%1").arg(semesterId);
    query.exec(str);
    select(query, res);
    return res;
}

//selectCourse(int courseId)
/*
 *=========================================================
 *  Three Overload methods
 *=========================================================
 */
//local method
inline void DatabaseIF::buildSelectCourse(QString & str) {
    str = "SELECT * FROM Course ";
}

vector< vector<string> > DatabaseIF::selectCourse() {  //get Course table
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectCourse(str);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectCourse(int courseId) {   //search by courseId
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectCourse(str);
    str += QString("WHERE courseId=%1").arg(courseId);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectCourse(string courseName) {   //search by courseName
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectCourse(str);
    str += QString("WHERE courseName='%1'").arg(QString::fromStdString(courseName));
    query.exec(str);
    select(query, res);
    return res;
}

//selectClass(int classId)
/*
 *=========================================================
 *  Two Overload methods
 *=========================================================
 */
//local method
inline void DatabaseIF::buildSelectClass(QString & str) {
    str = "SELECT * FROM Class ";
}

vector< vector<string> > DatabaseIF::selectClass() {  //get Class table
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectClass(str);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectClass(int classId) {   //search by classId
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectClass(str);
    str += QString("WHERE classId=%1").arg(classId);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectClassInSemester(int semesterId) {   //search by semesterId
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectClass(str);
    str += QString("WHERE semesterId=%1").arg(semesterId);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectClassByCourseName(string courseName) {   //search by courseName
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    str = QString("SELECT * FROM ((SELECT * FROM Class) NATURAL JOIN (SELECT * FROM Course)) WHERE courseName LIKE '%%1%'").arg(QString::fromStdString(courseName).toUpper());
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectClassWithLetterGradeRange(int classId) {   //search by classId and return a long one
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    str = QString("SELECT * FROM ((SELECT * FROM Class WHERE classId=%1) NATURAL JOIN (SELECT * FROM LetterGradeRange WHERE classId=%1))").arg(classId);
    query.exec(str);
    select(query, res);
    return res;
}

//selectClassInformation(string id);
//selectClassInformation(int classId);
//selectClassInformation(string id, int classId);
/*
 *=========================================================
 *  Four Overload methods
 *=========================================================
 */
//local method
inline void DatabaseIF::buildSelectClassInformation(QString & str) {
    str = "SELECT * FROM ClassInformation ";
}

vector< vector<string> > DatabaseIF::selectClassInformation() {   //get ClassInformation table
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectClassInformation(str);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectClassInformation(string id) { //search by student id
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectClassInformation(str);
    str += QString("WHERE id='%1'").arg(QString::fromStdString(id));
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectClassInformation(int classId) {    //search by classId
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectClassInformation(str);
    str += QString("WHERE classId=%1").arg(classId);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectClassInformation(string id, int classId) {    //search by student id and classId
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectClassInformation(str);
    str += QString("WHERE id='%1' AND classId=%2").arg(QString::fromStdString(id).arg(classId));
    query.exec(str);
    select(query, res);
    return res;
}

//selectActivity(int activityId);
/*
 *=========================================================
 *  Two Overload methods
 *  One additional method
 *=========================================================
 */
//local method
inline void DatabaseIF::buildSelectActivity(QString & str) {
    str = "SELECT * FROM Activity ";
}
vector< vector<string> > DatabaseIF::selectActivity() {  //get Activity table
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectActivity(str);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectActivity(int activityId) {   //search by activityId
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectActivity(str);
    str += QString("WHERE activityId=%1").arg(activityId);
    query.exec(str);
    select(query, res);
    return res;
}
//selectActivityInClass(int classId);   return activities in a class
vector< vector<string> > DatabaseIF::selectActivityInClass(int classId) {   //search by classId
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectActivity(str);
    str += QString("NATURAL JOIN (SELECT classId FROM Class WHERE classId=%1) GROUP BY activityId").arg(classId);
    query.exec(str);
    select(query, res);
    return res;
}

//selectGrade(string id);
//selectGrade(int activityId);
//selectGrade(string id, int activityId)
/*
 *=========================================================
 *  Four Overload methods
 *=========================================================
 */
//local method
inline void DatabaseIF::buildSelectGrade(QString & str) {
    str = "SELECT * FROM Grade ";
}
vector< vector<string> > DatabaseIF::selectGrade() { //get grade table
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectGrade(str);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectGrade(string id) {   //search by student id
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectGrade(str);
    str += QString("WHERE id='%1'").arg(QString::fromStdString(id));
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectGrade(int activityId) {  //search by activityId
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectGrade(str);
    str += QString("WHERE activityId=%1").arg(activityId);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectGrade(string id, int activityId) {  //search by student id and activityId
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectGrade(str);
    str += QString("WHERE activityId=%1 AND id='%2'").arg(activityId).arg(QString::fromStdString(id));
    query.exec(str);
    select(query, res);
    return res;
}

//selectLetterGradeRange(int classId)
/*
 *=========================================================
 *  Two Overload methods
 *=========================================================
 */
//local method
void DatabaseIF::buildSelectLetterGradeRange(QString & str) {
    str = "SELECT * FROM LetterGradeRange ";
}

vector< vector<string> > DatabaseIF::selectLetterGradeRange() {  //get LetterGradeRange table
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectLetterGradeRange(str);
    query.exec(str);
    select(query, res);
    return res;
}
vector< vector<string> > DatabaseIF::selectLetterGradeRange(int classId) {  //search by classId
    vector< vector<string> > res;
    QSqlQuery query;
    QString str;
    buildSelectLetterGradeRange(str);
    str += QString("WHERE classId=%1").arg(classId);
    query.exec(str);
    select(query, res);
    return res;
}
/*
 *=========================================================
 *Update
 *=========================================================
 */

//updateSemester(int semesterId, string year, string term);
/*
 *=========================================================
 *  One method
 *=========================================================
 */
bool DatabaseIF::updateSemester(int semesterId, string year, string term) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if (semesterId > 0) {
        str = QString("UPDATE Semester SET ");
        str += QString("year='%1', ").arg(QString::fromStdString(year));
        str += QString("term='%1' ").arg(QString::fromStdString(term));
        str += QString("WHERE semesterId=%1").arg(semesterId);
        res = query.exec(str);
    }
    return res;
}

//updateClass(int classId, string classSection, int courseId, int semesterId)
/*
 *=========================================================
 *  One method
 *=========================================================
 */
bool DatabaseIF::updateClass(int classId, string classSection, int courseId, int semesterId) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if (classId > 0) {
        str = QString("UPDATE Class SET ");
        str += QString("classSection='%1', ").arg(QString::fromStdString(classSection));
        str += QString("courseId=%1, ").arg(courseId);
        str += QString("semesterId=%1 ").arg(semesterId);
        str += QString("WHERE classId=%1").arg(classId);
        res = query.exec(str);
    }
    return res;
}

//letterGradeReleased(int classId, bool letterGradeReleased)
/*
 *=========================================================
 *  Special method
 *=========================================================
 */
bool DatabaseIF::letterGradeReleased(int classId, int letterGradeReleased) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if (classId > 0) {
        str = QString("UPDATE Class SET ");
        if (letterGradeReleased > 0) {
            str += QString("letterGradeReleased=1 ");
        }
        else {
            str += QString("letterGradeReleased=0 ");
        }

        str += QString("WHERE classId=%1").arg(classId);
        res = query.exec(str);
    }
    return res;
}

//updateClassInformation(string id, int classId, string letterGrade);
/*
 *=========================================================
 *  One method
 *=========================================================
 */
bool updateClassInformation(string id, int classId, string letterGrade) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if ((!id.empty()) && (classId > 0)) {
        str = QString("UPDATE ClassInformation SET ");
        str += QString("letterGrade='%1' ").arg(QString::fromStdString(letterGrade));
        str += QString("WHERE id='%1' AND classId=%2").arg(QString::fromStdString(id)).arg(classId);
        res = query.exec(str);
    }
    return res;
}

//updateActivity(int activityId, int classId, string activity, double maxMark, double weight)
/*
 *=========================================================
 *  One method
 *=========================================================
 */
bool DatabaseIF::updateActivity(int activityId, int classId, string activity, double maxMark, double weight) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if (activityId > 0) {
        str = QString("UPDATE Activity SET ");
        str += QString("classId=%1, ").arg(classId);
        str += QString("activity='%1', ").arg(QString::fromStdString(activity));
        str += QString("maxMark=%1, ").arg(maxMark);
        str += QString("weight=%1 ").arg(weight);
        str += QString("WHERE activityId=%1").arg(activityId);
        res = query.exec(str);
    }
    return res;
}

//updateGrade(string id, int activityId, double mark);
/*
 *=========================================================
 *  One method
 *=========================================================
 */
bool DatabaseIF::updateGrade(string id, int activityId, double mark) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if ((!id.empty()) && (activityId > 0)) {
        str = QString("UPDATE Grade SET ");
        if (mark < 0) {
            str += QString("mark=NULL");
        }
        else {
            str += QString("mark=%1 ").arg(mark);
        }
        str += QString("WHERE id='%1' AND activityId=%2").arg(QString::fromStdString(id)).arg(activityId);
        res = query.exec(str);
    }
    return res;
}

//updateLetterGradeRange(int classId, double, double, double, double, double, double, double, double, double, double, double);
/*
 *=========================================================
 *  One method
 *=========================================================
 */
bool DatabaseIF::updateLetterGradeRange(int classId, double scale1, double scale2, double scale3, double scale4, double scale5, double scale6, double scale7, double scale8, double scale9, double scale10, double scale11) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if (classId > 0) {
        str = QString("UPDATE LetterGradeRange SET ");
        str += QString("scale1=%1, ").arg(scale1);
        str += QString("scale2=%1, ").arg(scale2);
        str += QString("scale3=%1, ").arg(scale3);
        str += QString("scale4=%1, ").arg(scale4);
        str += QString("scale5=%1, ").arg(scale5);
        str += QString("scale6=%1, ").arg(scale6);
        str += QString("scale7=%1, ").arg(scale7);
        str += QString("scale8=%1, ").arg(scale8);
        str += QString("scale9=%1, ").arg(scale9);
        str += QString("scale10=%1, ").arg(scale10);
        str += QString("scale11=%1 ").arg(scale11);

        str += QString("WHERE classId=%1").arg(classId);
        res = query.exec(str);
    }
    return res;
}

/*
 *=========================================================
 *Delete
 *=========================================================
 */

//deleteSemester(int semesterId)
//deleteSemesterTrigger will delete corresponding tuples in Class table
/*
 *=========================================================
 * One method
 * One trigger
 *=========================================================
 */
bool DatabaseIF::deleteSemester(int semesterId) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if (semesterId > 0) {
        str = QString("DELETE FROM Semester WHERE semesterId=%1" ).arg(semesterId);
        res = query.exec(str);
    }
    return res;
}

void DatabaseIF::deleteSemesterTrigger() {
    QSqlQuery query;

    query.exec("DROP TRIGGER IF EXISTS 'main'.'DeleteSemesterTrigger'");
    query.exec("CREATE TRIGGER DeleteSemesterTrigger "
               "AFTER DELETE ON Semester "
               "FOR EACH ROW "
               "BEGIN DELETE FROM Class WHERE semesterId=old.semesterId; END");
}

//deleteClass(int classId)
//deleteClassTrigger will deleter corresponding tuples in ClassInformation and Activity table
/*
 *=========================================================
 * One method
 * One trigger
 *=========================================================
 */
bool DatabaseIF::deleteClass(int classId) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if (classId > 0) {
        str = QString("DELETE FROM Class WHERE classId=%1" ).arg(classId);
        res = query.exec(str);
    }
    return res;
}

void DatabaseIF::deleteClassTrigger() {
    QSqlQuery query;

    query.exec("DROP TRIGGER IF EXISTS 'main'.'DeleteClassTrigger'");
    query.exec("CREATE TRIGGER DeletClassTrigger "
               "AFTER DELETE ON Class "
               "FOR EACH ROW "
               "BEGIN DELETE FROM ClassInformation WHERE classId=old.classId; "
               "DELETE FROM Activity WHERE classId=old.classId; "
               "DELETE FROM LetterGradeRange WHERE classId=old.classId; END");
}

//deleteClassInformation(string id, int classId)
//deleteClassInformationTrigger will delete tuples in Grade table
/*
 *=========================================================
 * One method
 * One trigger
 *=========================================================
 */
bool DatabaseIF::deleteClassInformation(string id, int classId) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if ((!id.empty()) && (classId > 0)) {
        str = QString("DELETE FROM ClassInformation WHERE id='%1' AND classId=%2" ).arg(QString::fromStdString(id)).arg(classId);
        res = query.exec(str);
    }
    return res;
}

void DatabaseIF::deleteClassInformationTrigger() {
    QSqlQuery query;
    query.exec("DROP TRIGGER IF EXISTS 'main'.'DeleteClassInformationTrigger'");
    query.exec("CREATE TRIGGER DeleteClassInformationTrigger "
               "AFTER DELETE ON ClassInformation "
               "FOR EACH ROW "
               "BEGIN DELETE FROM Grade "
               "WHERE id=old.id AND "
               "(activityId IN (SELECT activityId FROM Activity WHERE classId=old.classId)); END");
}

//deleteActivity(int activityId)
//deleteActivityTrigger will delete corresponding tuples in Grade table
/*
 *=========================================================
 * One method
 * One trigger
 *=========================================================
 */
bool DatabaseIF::deleteActivity(int activityId) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if (activityId > 0) {
        str = QString("DELETE FROM Activity WHERE activityId=%1").arg(activityId);
        res = query.exec(str);
    }
    return res;
}

void DatabaseIF::deleteActivityTrigger() {
    QSqlQuery query;
    query.exec("DROP TRIGGER IF EXISTS 'main'.'DeleteActivityTrigger'");
    query.exec("CREATE TRIGGER DeleteActivityTrigger "
               "AFTER DELETE ON Activity "
               "FOR EACH ROW "
               "BEGIN DELETE FROM Grade "
               "WHERE activityId=old.activityId; END");
}

//deleteGrade(string id, int activityId)
//no trigger
/*
 *=========================================================
 * One method
 *=========================================================
 */
bool DatabaseIF::deleteGrade(string id, int activityId) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if (activityId > 0) {
        str = QString("DELETE FROM Grade WHERE activityId=%1 AND id='%2'").arg(activityId).arg(QString::fromStdString(id));
        res = query.exec(str);
    }
    return res;
}

//deleteLetterGradeRange(int classId)
//no trigger
/*
 *=========================================================
 * One method
 *=========================================================
 */
bool DatabaseIF::deleteLetterGradeRange(int classId) {
    bool res = false;
    QSqlQuery query;
    QString str;
    if (classId > 0) {
        str = QString("DELETE FROM LetterGradeRange WHERE classId=%1").arg(classId);
        res = query.exec(str);
    }
    return res;
}
