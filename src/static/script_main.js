document.addEventListener('DOMContentLoaded', () => {
    const grid = document.getElementById('video-grid');

    // --- СИМУЛЯЦИЯ ДАННЫХ ---
    // В будущем эти данные придут от твоего C++ сервера через fetch('/api/get_videos')
    const mockVideos = [
        { id: 1, title: 'Как я написал HTTP сервер на C++', views: '1.2K', date: '2 дня назад' },
        { id: 2, title: 'Обзор Sockets API для новичков', views: '540', date: '5 дней назад' },
        { id: 3, title: 'Красивый CSS за 5 минут', views: '8K', date: '1 неделю назад' },
        { id: 4, title: 'Курсовая работа: Видеохостинг', views: '120', date: 'Сегодня' },
        { id: 5, title: 'Тест загрузки видео', views: '10', date: 'Сейчас' }
    ];

    // Функция отрисовки карточек
    function renderVideos(videos) {
        grid.innerHTML = ''; // Очистить сетку

        videos.forEach(video => {
            // Создаем HTML элемент карточки
            const card = document.createElement('article');
            card.className = 'video-card';

            // Клик по карточке ведет на просмотр (endpoint придумай сам, например /watch?id=...)
            card.onclick = () => {
                window.location.href = `/watch?v=${video.id}`;
            };

            // Формируем внутренний HTML
            // Вместо <img> пока стоит div.thumbnail. Потом заменишь на <img src="...">
            card.innerHTML = `
                <div class="thumbnail">
                    ▶
                </div>
                <div class="video-info">
                    <h3 class="video-title">${video.title}</h3>
                    <div class="video-meta">
                        <span>${video.views} просмотров</span> • 
                        <span>${video.date}</span>
                    </div>
                </div>
            `;

            grid.appendChild(card);
        });
    }

    // Вызываем отрисовку
    renderVideos(mockVideos);

    /*
    // --- ПРИМЕР БУДУЩЕЙ ЛОГИКИ ЗАГРУЗКИ (AJAX) ---
    fetch('/api/videos-list')
        .then(response => response.json())
        .then(data => renderVideos(data))
        .catch(error => console.error('Ошибка загрузки списка:', error));
    */
});