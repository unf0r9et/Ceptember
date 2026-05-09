![Micro-framework Ceptember](assets/LOGO.jpg)
> *Эта работа — всего лишь мой курсовой проект, и она не претендует на звание коммерческого продукта. Тем не менее, проект **достоин** вашего внимания!*
> <p align="right"><i>С любовью, Серёжа =)</i></p>

---

# Что такое CEPTEMBER? 🤔

**CEPTEMBER** - это микрофреймворк для удобной работы с HTTP-запросами. Он написан на **C++** с использованием **Linux Socket API** и нескольких архитектурных решений, о которых будет рассказано ниже.

## Почему Linux? 🐧
Ответ прост: я сам пользуюсь Linux, и подавляющее большинство серверов в мире работают именно на этой ОС. 

---

# Начало работы

## Работа со статическими файлами (HTML, CSS, JS) 📁

Для работы со статическими файлами просто поместите их в папку `static`.  
Всё остальное **CEPTEMBER** сделает за вас. Лишь пара уточнений:

* **Для главной страницы:** файлы (`html`, `css`, `js`) нужно разместить в корне папки `static`.
* **Для других страниц:** название вложенной папки в каталоге `static` должно совпадать с путём (URL), по которому будет доступна страница.  
  *(Пример: если страница должна открываться по пути `/uploadVideo`, то и папка должна называться `uploadVideo`. В неё вы помещаете все нужные файлы)*.
* **Имена файлов:** все HTML-файлы должны называться `index.html`. JS и CSS-файлы могут иметь любые уникальные названия.

---

## Обработка HTTP-запросов 🛠

Все обработчики находятся по пути `src/main/handlers`. Там вы найдете 4 файла: `DELETE.cpp`, `GET.cpp`, `POST.cpp`, `PUT.cpp`.

В них уже написаны примеры кода. Рассмотрим работу на примере **GET-запроса**:

```c++
#include "httpController.hpp"

extern thread_local requestEntity rqEntity;

std::string httpController::methods_GET() {
    switch (str_hash_for_switch(rqEntity.path)) {
        case "/"_hash:
            // Логика для главной страницы
        default:
            return HTTP_RESPONSE_404;
    }
}
```

### 💡 Фишка: Switch-case со строками
Одной из особенностей проекта является возможность использовать `switch` со строковыми значениями (URI).
*   Синтаксис: `case "/ваш_путь"_hash:`.
*   Обязательно добавляйте суффикс `_hash` после строки.

---

## Сущность запроса (requestEntity) 📦

Для работы с данными запроса используется класс `requestEntity`. Он предоставляет удобный доступ ко всем частям HTTP-пакета:

```c++
class requestEntity {
public:
    std::string method;   // Метод (GET, POST и т.д.)
    std::string path;     // Путь запроса
    std::vector<std::pair<std::string, std::string>> headers; // Заголовки
    std::string body;     // Тело запроса
};
```

> **Важно:** Если тело запроса слишком большое (например, при передаче бинарных файлов), оно автоматически сохраняется на диск.
> А в поле тела хранится путь к файлу.

---

## Сохранение файлов (fileSaver) 💾

Для удобного сохранения полученных данных предусмотрен класс `fileSaver`. Вам не нужно вручную обрабатывать потоки байтов:

```c++
// Примеры методов сохранения:
static int saveVideo(const requestEntity &request, const std::string &directoryPath);
static int saveDocs(const requestEntity &request, const std::string &directoryPath);
static int savePhoto(const requestEntity &request, const std::string &directoryPath);
static int saveTxt(const requestEntity &request, const std::string &directoryPath);
```
Просто передайте объект `requestEntity` и путь к директории — **CEPTEMBER** сделает всё за вас.

---

## Формирование ответов 📤

В проекте реализовано два удобных инструмента для ответов:

### 1. basicResponse
Содержит готовые константы стандартных ответов. Например:
*   `HTTP_RESPONSE_404` (Not Found)
*   `HTTP_RESPONSE_405` (Method Not Allowed)
    Полный список можно найти непосредственно в коде класса.

### 2. responseBuilder
Гибкий класс для создания кастомных ответов с использованием паттерна "Builder".

**Пример использования констант и типов:**
```c++
#define HTTP_OK 200
#define MIME_TEXT_HTML "text/html"
#define MIME_VIDEO_MP4 "video/mp4"
```

**Методы сборки ответа:**
```c++
responseBuilder builder;
std::string response = builder
    .setStatusCode(HTTP_OK)
    .setContentTypeHeader(MIME_TEXT_HTML)
    .setContent("Hello World!")
    .buildResponse();
```

### Передача бинарных файлов (Video/Images) 🎬
Для отправки тяжелых файлов сначала строится заголовок, а затем файл привязывается к телу ответа:

```c++
responseBuilder builder;
std::string response = builder
        .setStatusCode(HTTP_OK)
        .setContentTypeHeader(MIME_VIDEO_MP4)
        .setContentLengthHeader(std::filesystem::file_size("path/to/video.mp4"))
        .addHeader("Accept-Ranges", "bytes")
        .setConnectionHeader(true)
        .buildResponse();

builder.addBinaryContent("path/to/video.mp4"); // Привязка контента
return response;
```

---
На этом всё! Удачи в использовании **CEPTEMBER** и ваших будущих проектах!
