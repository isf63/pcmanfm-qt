/*
    Copyright (C) 2017 Pedram Pourang (Tsu Jan) <tsujan2000@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef PCMANFM_BULKRENAME_H
#define PCMANFM_BULKRENAME_H

#include "ui_bulk-rename.h"
#include <QDialog>

#include <libfm-qt6/core/fileinfo.h>

namespace PCManFM {

class BulkRenameDialog : public QDialog {
Q_OBJECT

public:
    explicit BulkRenameDialog(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    // renaming
    QString getBaseName() const {
        return ui.lineEdit->text();
    }
    int getStart() const {
        return ui.spinBox->value();
    }
    bool getZeroPadding() const {
        return ui.zeroBox->isChecked();
    }
    bool getRespectLocale() const {
        return ui.localeBox->isChecked();
    }

    // replacement
    bool getReplace() const {
        return ui.replaceGroupBox->isChecked();
    }
    QString getFindStr() const {
        return ui.findLineEdit->text();
    }
    QString getReplaceStr() const {
        return ui.replaceLineEdit->text();
    }
    Qt::CaseSensitivity getCase() const {
        return ui.caseBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    }
    bool getRegex() const {
        return ui.regexBox->isChecked();
    }

    // case change
    bool getCaseChange() const {
        return ui.caseGroupBox->isChecked();
    }
    bool getUpperCase() const {
        return ui.upperCaseButton->isChecked();
    }

    void setState(const QString& baseName,
                  const QString& findStr, const QString& replaceStr,
                  bool replacement, bool caseChange,
                  bool zeroPadding, bool respectLocale, bool regex, bool toUpperCase,
                  int start, Qt::CaseSensitivity cs);

protected:
    virtual void showEvent(QShowEvent* event) override;

private:
    Ui::BulkRenameDialog ui;
};

class BulkRenamer {
public:
    BulkRenamer(const Fm::FileInfoList& files, QWidget* parent = nullptr);
    ~BulkRenamer();

private:
    bool rename(const Fm::FileInfoList& files,
                QString& baseName, const QLocale& locale,
                int start, bool zeroPadding, bool respectLocale,
                QWidget* parent);
    bool renameByReplacing(const Fm::FileInfoList& files,
                           const QString& findStr, const QString& replaceStr,
                           Qt::CaseSensitivity cs, bool regex,
                           QWidget* parent);
    bool renameByChangingCase(const Fm::FileInfoList& files, const QLocale& locale,
                              bool toUpperCase, QWidget* parent);
};

}

#endif // PCMANFM_BULKRENAME_H
