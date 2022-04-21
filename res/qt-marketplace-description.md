# Qt Pdf Viewer Library
The `qt-pdf-viewer-library` is a `qml` wrapper of `pdf.js` library which allows you to render `PDF` files in a `WebView`. This library also works for Android devices, and it uses `WebSocketServer`, `WebSocketTransport` and `WebChannel` to exchange data between qml and the browser environment.

### Dependencies
The `qt modules` needed by the library are:
- `webchannel`
- `websockets`
- `webview`

### Features
- the library is `open source` (`Apache-2.0` license)

- the library supports `desktop`, `embedded`, and `android` devices

- the library allows PDF `rotation`, `zoom in/out`, `text search`, `scroll mode`, `scale mode`, `change view visualization`, pages `preview`, error handling

- the library is `UI indipendent`: all operations on the PDF are provided by the `PdfView` component.
- easy setup
- more info can be found on [github](https://github.com/develtar/qt-pdf-viewer-library)

### Testing
The `qt-pdf-viewer-library` has been tested on the following `qt` versions:

- `Qt 5.12.4` (Desktop)
- `Qt 5.15.2` (Desktop and Android)
- `Qt 6.2.2` (Desktop)

on the following `Android` devices:
- `Galaxy Nexus, API 22, Android 5.1`
- `Nexus S, API 23, Android 6.0`
- `Nexus S, API 24, Android 7.0`
- `Pixel 2 XL, API 27, Android 8.1`
- `Pixel 4, API 28, Android 9.0`
- `Redmi Note 8 pro, API 29, Android 10`
- `Nexus 5X, API 29, Android 10`
- `Nexus 10, API 30, Android 11`
- `Pixel XL, API 30, Android 11`

and on the following `os`:
- `Linux KDE 20.04`

### Screenshots
The sample app and the screenshots can be found on [github](https://github.com/develtar/qt-pdf-viewer-library).
