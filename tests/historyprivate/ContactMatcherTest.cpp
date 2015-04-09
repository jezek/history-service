/*
 * Copyright (C) 2015 Canonical, Ltd.
 *
 * This file is part of history-service.
 *
 * history-service is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * history-service is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <QContactManager>
#include <QContact>
#include <QContactExtendedDetail>
#include <QContactPhoneNumber>
#include <QContactName>

#include "telepathytest.h"
#include "contactmatcher_p.h"
#include "types.h"
#include "phoneutils_p.h"

QTCONTACTS_USE_NAMESPACE

class ContactMatcherTest : public TelepathyTest
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void init();
    void clean();
    void testMatchExistingContact_data();
    void testMatchExistingContact();
private:
    QContactManager *mContactManager;
    QContact mPhoneContact;
    QContact mExtendedContact;
};

void ContactMatcherTest::initTestCase()
{
    initialize();
    mContactManager = new QContactManager("memory");
    ContactMatcher::instance(mContactManager);

    // create two contacts to test
    QContactPhoneNumber phoneNumber;
    phoneNumber.setNumber("12345678");
    QVERIFY(mPhoneContact.saveDetail(&phoneNumber));
    QContactPhoneNumber phoneNumber2;
    phoneNumber2.setNumber("87654321");
    QVERIFY(mPhoneContact.saveDetail(&phoneNumber2));
    QContactName name;
    name.setFirstName("Phone");
    name.setLastName("Contact");
    QVERIFY(mPhoneContact.saveDetail(&name));
    QVERIFY(mContactManager->saveContact(&mPhoneContact));

    QContactExtendedDetail extendedDetail;
    extendedDetail.setName("x-mock-im");
    extendedDetail.setData("12345678");
    QVERIFY(mExtendedContact.saveDetail(&extendedDetail));
    name.setFirstName("Extended");
    name.setLastName("Generic Contact");
    QVERIFY(mExtendedContact.saveDetail(&name));
    QVERIFY(mContactManager->saveContact(&mExtendedContact));
}

void ContactMatcherTest::init()
{
    // just add two telepathy mock accounts to make sure we get the addressable fields correctly
    addAccount("mock", "mock", "generic account");
    addAccount("mock", "ofono", "phone account");
}

void ContactMatcherTest::clean()
{
    doCleanup();
}

void ContactMatcherTest::testMatchExistingContact_data()
{
    QTest::addColumn<QString>("accountId");
    QTest::addColumn<QString>("identifier");
    QTest::addColumn<QString>("contactId");
    QTest::addColumn<bool>("phoneNumberCompare");

    QTest::newRow("match exact phone id") << QString("mock/ofono/account0") << QString("12345678") << mPhoneContact.id().toString() << false;
    QTest::newRow("match phone number with prefix") << QString("mock/ofono/account0") << QString("+187654321") << mPhoneContact.id().toString() << true;
    QTest::newRow("match exact extra id") << QString("mock/mock/account0") << QString("12345678") << mExtendedContact.id().toString() << false;
}

void ContactMatcherTest::testMatchExistingContact()
{
    QFETCH(QString, accountId);
    QFETCH(QString, identifier);
    QFETCH(QString, contactId);
    QFETCH(bool, phoneNumberCompare);

    QSignalSpy contactInfoSpy(ContactMatcher::instance(), SIGNAL(contactInfoChanged(QString,QString,QVariantMap)));
    QVariantMap info = ContactMatcher::instance()->contactInfo(accountId, identifier);
    if (phoneNumberCompare) {
        QVERIFY(PhoneUtils::comparePhoneNumbers(info[History::FieldIdentifier].toString(), identifier));
    } else {
        QCOMPARE(info[History::FieldIdentifier].toString(), identifier);
    }

    QTRY_COMPARE(contactInfoSpy.count(), 1);
    QCOMPARE(contactInfoSpy.first()[0].toString(), accountId);
    QCOMPARE(contactInfoSpy.first()[1].toString(), identifier);
    info = contactInfoSpy.first()[2].toMap();
    QCOMPARE(info[History::FieldContactId].toString(), contactId);
    if (phoneNumberCompare) {
        QVERIFY(PhoneUtils::comparePhoneNumbers(info[History::FieldIdentifier].toString(), identifier));
    } else {
        QCOMPARE(info[History::FieldIdentifier].toString(), identifier);
    }
}

QTEST_MAIN(ContactMatcherTest)
#include "ContactMatcherTest.moc"