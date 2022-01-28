#include "testentityif.h"


void TestEntityIF::testUserFromJson()
{
    QString jsonString = "{\"idUser\": 11,\"username\": \"d.salvetti1\","
                         "\"name\": \"Davide\", \"surname\": \"Salvetti\","
                         "\"address\": \"Via Nazionale 21\", \"cellNumber\": \"3470000000\","
                         "\"sex\": \"M\", \"email\": \"d.salvetti1@studenti.unibg.it\","
                         "\"idTeam\": 3, \"role\": \"FOREMAN\", \"state\": \"ACTIVE\","
                         "\"cf\": \"SLVDVD97A00A000A\" }";

    accountmanagementIF::User *user = new accountmanagementIF::User();
    user->fromJsonObject(QJsonDocument::fromJson(jsonString.toUtf8()).object());

    QVERIFY(user->getIdUser() == 11);
    QVERIFY(user->getUsername() == "d.salvetti1");
    QVERIFY(user->getName() == "Davide");
    QVERIFY(user->getAddress() == "Via Nazionale 21");
    QVERIFY(user->getCellnumber() == "3470000000");
    QVERIFY(user->getCf() == "SLVDVD97A00A000A");
    QVERIFY(user->getRole() == 1);
    QVERIFY(user->getSurname() == "Salvetti");
    QVERIFY(user->getSex() == "M");
    QVERIFY(user->getState() == 1);
    QVERIFY(user->getTeam() == 3);
}

void TestEntityIF::testTeamFromJson()
{
    QString jsonString = "{\"idTeam\":1,\"teamName\":\"BGTeam\",\"idForeman\":4,"
                         "\"users\":[{\"idUser\":1,\"username\":\"admin\",\"name\":\"Mario\","
                         "\"surname\":\"Rossi\",\"address\":\"Via Nazionale 7\",\"cellNumber\":"
                         "\"3485556255\",\"sex\":\"M\",\"email\":\"mario@rossi.it\","
                         "\"idTeam\":1,\"role\":\"ADMINISTRATOR\",\"state\":\"ACTIVE\",\"cf\":\"MRARSS80A01C800V\"},{"
                         "\"idUser\":2,\"username\":\"admin1\",\"name\":\"Daniela\",\"surname\":\"Rossi\",\"address\":"
                         "\"Via Nazionale 8\",\"cellNumber\":\"325186255\",\"sex\":\"F\",\"email\":\"daniela@rossi.it\","
                         "\"idTeam\":1,\"role\":\"ADMINISTRATOR\",\"state\":\"ACTIVE\",\"cf\":\"DNARSS80A01C800V\"}"
                         "],\"area\":{\"idArea\":1,\"areaName\":\"Bergamo\",\"lat\":45.69499969482422,\"lng\":9.670000076293945,\"istatCode\":\"016024\"}}";

    teamManagementIF::Team *team = new teamManagementIF::Team();
    team->fromJsonObject(QJsonDocument::fromJson(jsonString.toUtf8()).object());

    QVERIFY(team->getTeamName() ==  "BGTeam");
    QVERIFY(team->getIdTeam() == 1);
    QVERIFY(team->getIdForeman() == 4);

    areaInformationManagementIF::Area *area = team->getArea();

    QVERIFY(area->getAreaName() == "Bergamo");
    QVERIFY(area->getIstatCode() == "016024");
    QVERIFY(area->getIdArea() == 1);
    QVERIFY(area->getLat() == 45.69499969482422);
    QVERIFY(area->getLng() == 9.670000076293945);

    QList<accountmanagementIF::User *> users = team->getUsers();

    QVERIFY(users.at(0)->getUsername() == "admin");
    QVERIFY(users.at(0)->getName() == "Mario");
    QVERIFY(users.at(0)->getSurname() == "Rossi");

    QVERIFY(users.at(1)->getUsername() == "admin1");
    QVERIFY(users.at(1)->getName() == "Daniela");
    QVERIFY(users.at(1)->getSurname() == "Rossi");
}

void TestEntityIF::testAreaFromJson()
{
    QString jsonString = "{\"idArea\":3,\"areaName\":\"Costa di Mezzate\",\"lat\":45.66666793823242,"
                         "\"lng\":9.800000190734863,\"istatCode\":\"016084\"}";

    areaInformationManagementIF::Area *area = new areaInformationManagementIF::Area();
    area->fromJsonObject(QJsonDocument::fromJson(jsonString.toUtf8()).object());

    QVERIFY(area->getAreaName() == "Costa di Mezzate");
    QVERIFY(area->getIstatCode() == "016084");
    QVERIFY(area->getIdArea() == 3);
    QVERIFY(area->getLat() == 45.66666793823242);
    QVERIFY(area->getLng() == 9.800000190734863);
}

void TestEntityIF::testAprsDataFromJson()
{
    QString jsonString = "{\"name\":\"cw6134\",\"time\":\"28-01-2022 01:10:13\",\"temperature\":0.0,"
                         "\"pressure\":1024.2,\"humidity\":95,\"windDirection\":180.0,\"windSpeed\":0.4,"
                         "\"windGust\":1.3,\"rainOneHour\":0.0,\"rainDay\":0.0,\"rainMidNight\":0.0,\"luminosity\":null}";

    areaInformationManagementIF::AprsData *aprs = new areaInformationManagementIF::AprsData();
    aprs->fromJsonObject(QJsonDocument::fromJson(jsonString.toUtf8()).object());

    QVERIFY(aprs->getName() == "cw6134");
    QVERIFY(aprs->getDate() == "28-01-2022 01:10:13");
    QVERIFY(qFuzzyCompare(aprs->getPressure(), 1024.2f));
    QVERIFY(qFuzzyCompare(aprs->getTemperature(), 0.0f));
    QVERIFY(qFuzzyCompare(aprs->getWindDirection(), 180.0f));
    QVERIFY(qFuzzyCompare(aprs->getWindSpeed(), 0.4f));
    QVERIFY(qFuzzyCompare(aprs->getWindGust(), 1.3f));
    QVERIFY(aprs->getHumidity() == 95);
    QVERIFY(aprs->getRainOneHour() == 0.0);
    QVERIFY(aprs->getRainDay() == 0.0);
    QVERIFY(aprs->getRainMidNight() == 0.0);
}

void TestEntityIF::testAlarmFromJson()
{
    QString jsonString = "{\"idAlarm\":4,\"time\":\"26-01-2022 18:12:24\",\"type\":"
                         "\"FROST\",\"color\":\"GREEN\",\"idArea\":1,\"description\":\"no description\"}";

    areaInformationManagementIF::Alarm *alarm = new areaInformationManagementIF::Alarm();
    alarm->fromJsonObject(QJsonDocument::fromJson(jsonString.toUtf8()).object());

    QVERIFY(alarm->getIdArea() == 1);
    QVERIFY(alarm->getDate() == "26-01-2022 18:12:24");
    QVERIFY(alarm->getColor() == "GREEN");
    QVERIFY(alarm->getType() == "FROST");
    QVERIFY(alarm->getDescription() == "no description");
}


QTEST_MAIN(TestEntityIF)

