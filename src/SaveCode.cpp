/* Scout Talker - Scouting codes, ciphers and encryption program
 * Copyright (C) 2015 by Diana Capela
 *                       João  Santos    (joaompssantos@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "SaveCode.h"

//#include <QFile>
#include <QFileDialog>
//#include <QFileInfo>
#include <QPainter>
#include <QPrinter>
#include <QTextDocumentWriter>
#include <QTextEdit>
#include <QTextStream>

// Needed to use static variable
QString SaveCode::lastPath;

/** Constructor **/
SaveCode::SaveCode(savingTypes saveType, QTextEdit *textedit) : QObject() {
    savingType = saveType;
    textEdit = textedit; // TODO: check this

    lastPath = QDir::homePath();
}

/** Private Methods **/
void SaveCode::saveAsPNG() {
    // Set text width
    textEdit->document()->setTextWidth(580);

    // Store original font size
    int fontSize = textEdit->font().pointSize();

    // Copy original font
    QFont aux_font = textEdit->font();

    // Add 10pt to original font size
    aux_font.setPointSize(fontSize + 15);
    textEdit->setFont(aux_font);

    // Create image by calculating the size from QTextEdit
    QImage *code = new QImage(
            QSize((int) (textEdit->document()->size().width() * 1.05),
                  (int) (textEdit->document()->size().height() * 1.05)),
            QImage::Format_ARGB32_Premultiplied);

    // Fill image with white
    code->fill(Qt::white);

    // Initialise QPainter
    auto *painter = new QPainter(code);

    // Set QPainter font
    painter->setFont(textEdit->font());
    // Set text colour
    painter->setPen(textEdit->textColor());

    // Draw text with painter to image (The text is justified, vertically centred and using word wrap to code->rect())
    painter->drawText(
            QRect((int) (textEdit->document()->size().width() * 0.05 / 2),
                  (int) (textEdit->document()->size().height() * 0.05 / 2),
                  (int) (textEdit->document()->size().width()), (int) (textEdit->document()->size().height())),
            Qt::AlignJustify | Qt::AlignVCenter | Qt::TextWordWrap, textEdit->toPlainText());

    // Save image to file
    code->save(fileName, "PNG");

    // Restore original font size
    aux_font.setPointSize(fontSize);
    textEdit->setFont(aux_font);
}

void SaveCode::saveAsPDF() {
    QTextDocument document;
    document.setPlainText(textEdit->toPlainText());

    // Set document size
//        textEdit->document()->setTextWidth(580);
    // TODO: PASSAR PARA TAMANHOS A4 (WIDTH) ESPECIALMENTE SE O TEXTO FOR MUITO GRANDE (HEIGHT)

    // Store original font size
    int fontSize = textEdit->font().pointSize();

    // Copy original font
    QFont aux_font = textEdit->font();

    // Add 10pt to original font size
    aux_font.setPointSize(textEdit->font().pointSize());
    aux_font.setPointSize(15);
    textEdit->setFont(aux_font);

    // Calculate paper sizes
    QSizeF pageSize = textEdit->document()->size();
    pageSize.setWidth(pageSize.width() * 1.05);
    pageSize.setHeight(pageSize.height() * 1.05);


    pageSize.setWidth(QPrinter::A4);
    pageSize.setHeight(QPrinter::A4);
//        textEdit->document()->setTextWidth(pageSize.width() * 0.95);
    // Set document size
//        textEdit->document()->setPageSize(pageSize);

    // Printer options
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setFullPage(true);
    printer.setPageSize(QPrinter::A4);
    printer.setPageMargins(20, 20, 20, 20, QPrinter::Millimeter);
//        printer.setPageSize(QPageSize(pageSize, QPageSize::Point, QString(), QPageSize::ExactMatch));
    printer.setOutputFileName(fileName);

    // Print PDF file
//        textEdit->document()->setPageSize(printer.pageRect().size()); // To ignore page numbers
//        textEdit->document()->print(&printer);

//        document.setPageSize(printer.pageRect().size() * 0.5); // To ignore page numbers
//        document.setPageSize(printer.paperRect().size());
    document.setDefaultFont(textEdit->font());
//    printf("%d\n", textEdit->font().pointSize());
    document.setPageSize(QPageSize::definitionSize(QPageSize::A4));
//        document.setPageSize(QSizeF(QSize(210, 297, QPrinter::Millimeter)));
    document.print(&printer);

    // Restore original font size
    aux_font.setPointSize(fontSize);
    textEdit->setFont(aux_font);
}

void SaveCode::saveAsODT() {
    QTextDocument *textDocument = textEdit->document();

    QTextDocumentWriter writer;
    writer.setFormat("ODT");
    writer.setFileName(fileName);
    writer.write(textDocument);
}

void SaveCode::saveAsTXT() {
    // Open file to write
    QFile file(fileName);
    file.open(QFile::WriteOnly);

    // Initialise text stream
    QTextStream write(&file);

    // Write to file
    write << textEdit->toPlainText();
    write.flush();

    // Close file
    file.close();
}

/** Public slots **/
// TODO: Create protections and checks (ex: check if file was successfully saved)
void SaveCode::saveFile() {
    // Create list of possible extensions based on saving type
    QString formats;

    switch (savingType) {
        case savingTypes::All:
            formats = tr("Portable Network Graphics (*.png);;Portable Document Format (*.pdf);;"
                         "Open Document Format (*.odt);;Text file (*.txt)");

            break;

//        case savingTypes::Font:
//            formats = tr("Portable Network Graphics (*.png);;Portable Document Format (*.pdf);;"
//                         "Open Document Format (*.odt)"); // TODO: Doesn't seem to be possible to select font on odt file

//            break;

        case savingTypes::Font:
        case savingTypes::Image:
            formats = tr("Portable Network Graphics (*.png);;Portable Document Format (*.pdf)");

            break;

        default:
            formats = tr("Portable Network Graphics (*.png);;Portable Document Format (*.pdf);;"
                         "Open Document Format (*.doc);;Text file (*.txt)");

            break;
    }

    // Create new file dialog, named "Save as" and starting at the home directory
    fileName = QFileDialog::getSaveFileName(nullptr, tr("Save as..."), lastPath, formats);

    // If string is empty, for instance due to cancellation, skips the saving to file
    if (fileName.isEmpty()) {
        return;
    }

    // Choose the proper saving method according to extension
    QFileInfo fileInfo(fileName);
    auto suffix = fileInfo.suffix();
    lastPath = fileInfo.absolutePath();

    if (QString::compare(suffix, "png", Qt::CaseInsensitive) == 0) {
        saveAsPNG();
    }
    else if (QString::compare(suffix, "pdf", Qt::CaseInsensitive) == 0) {
        saveAsPDF();
    }
    else if (QString::compare(suffix, "odt", Qt::CaseInsensitive) == 0) {
        saveAsODT();
    }
    else if (QString::compare(suffix, "txt", Qt::CaseInsensitive) == 0) {
        saveAsTXT();
    }
    else {
        // Should never be reached
        exit (EXIT_FAILURE);
    }
}