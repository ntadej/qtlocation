/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
** This file is part of the Nokia services plugin for the Maps and
** Navigation API.  The use of these services, whether by use of the
** plugin or by other means, is governed by the terms and conditions
** described by the file NOKIA_TERMS_AND_CONDITIONS.txt in
** this package, located in the directory containing the Nokia services
** plugin source code.
**
****************************************************************************/

#ifndef QPLACEDETAILSREPLYIMPL_H
#define QPLACEDETAILSREPLYIMPL_H

#include <QtNetwork/QNetworkReply>
#include <QtLocation/QPlaceDetailsReply>

QT_BEGIN_NAMESPACE

class QPlaceManager;
class QPlaceManagerEngineNokiaV2;

class QPlaceDetailsReplyImpl : public QPlaceDetailsReply
{
    Q_OBJECT

public:
    QPlaceDetailsReplyImpl(QNetworkReply *reply, QPlaceManagerEngineNokiaV2 *parent);
    ~QPlaceDetailsReplyImpl();

    void abort();
    void setPlaceId(const QString &placeId) { m_placeId = placeId; }

private slots:
    void setError(QPlaceReply::Error error_, const QString &errorString);
    void replyFinished();

private:
    QNetworkReply *m_reply;
    QPlaceManagerEngineNokiaV2 *m_engine;
    QString m_placeId;
};

QT_END_NAMESPACE

#endif // QPLACEDETAILSREPLYIMPL_H
