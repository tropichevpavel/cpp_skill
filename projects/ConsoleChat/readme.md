# ConsoleChat

## Краткое описание
Консольный чат представлять из себя консольное страничное приложение, для обмена сообщениями между зарегистрированными пользователями как в общем чате, так и в личном.

## Сущности
1. Пользователь
   - ID
   - Имя
   - Логин
   - Пароль
2. Чат
   - ID
   - Массив сообщений
3. Сообщение
   - ID
   - ID пользователя от кого
   - ID пользователя кому
   - текст

## Дополнительные классы
1. App - класс-обертка, является основой приложения, хранит информацию о пользователях и чатах.
2. UI - класс-обертка пользовательского интерфейса, отвечает за навигацию и хранения состояния страниц
   - PageState - класс-обертка для хранения состояния страницы
   - Menu и Option - классы для хранения списка меню
3. AnyData - класс позволяющий хранить любой тип данных

## Разработчики
Данный проект был спроектирован и разработан единолично.