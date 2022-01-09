import QtQuick 2.0

import "../components" as CustomComponents
import "../"

BaseOptionSection {
    title: "Search text:"

    CustomComponents.TextField {
        id: tfSearch
        width: 100

        textInput {
            onTextChanged: {
                pdfView.searchText(textInput.text)
            }
        }
    }


    CustomComponents.Button{
        image.source: "qrc:/icons/backward_white_24dp.svg"

        onClicked: {
            pdfView.searchTextOccurance(tfSearch.textInput.text, true, false, true, true)
        }
    }
    CustomComponents.Button{
        image.source: "qrc:/icons/forward_white_24dp.svg"

        onClicked: {
            pdfView.searchTextOccurance(tfSearch.textInput.text, true, false, true, false)
        }
    }



}
