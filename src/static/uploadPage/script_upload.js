const dropZone = document.getElementById('dropZone');
const fileInput = document.getElementById('videoInput');
const detailsStep = document.getElementById('detailsStep');
const startUploadBtn = document.getElementById('startUploadBtn');
const removeFileBtn = document.getElementById('removeFileBtn');
const titleInput = document.getElementById('videoTitle');

// Элементы информации о файле
const fileName = document.getElementById('fileName');
const fileSize = document.getElementById('fileSize');

// Прогресс
const progressContainer = document.getElementById('progressContainer');
const progressFill = document.getElementById('progressFill');
const progressText = document.getElementById('progressText');
const statusText = document.getElementById('status');

let selectedFile = null;

// --- Drag & Drop логика ---
dropZone.addEventListener('click', () => fileInput.click());

['dragenter', 'dragover', 'dragleave', 'drop'].forEach(eventName => {
    dropZone.addEventListener(eventName, (e) => {
        e.preventDefault();
        e.stopPropagation();
    }, false);
});

['dragenter', 'dragover'].forEach(eventName => {
    dropZone.addEventListener(eventName, () => dropZone.classList.add('dragover'), false);
});

['dragleave', 'drop'].forEach(eventName => {
    dropZone.addEventListener(eventName, () => dropZone.classList.remove('dragover'), false);
});

dropZone.addEventListener('drop', (e) => handleFiles(e.dataTransfer.files));
fileInput.addEventListener('change', (e) => handleFiles(e.target.files));

// --- Обработка выбора файла ---
function handleFiles(files) {
    if (files.length === 0) return;
    const file = files[0];

    if (!file.type.startsWith('video/')) {
        showStatus('Это не видеофайл!', 'error');
        return;
    }

    selectedFile = file;

    // Скрываем зону загрузки, показываем форму деталей
    dropZone.style.display = 'none';
    detailsStep.style.display = 'block';

    // Заполняем инфо
    fileName.textContent = file.name;
    fileSize.textContent = (file.size / (1024 * 1024)).toFixed(2) + ' MB';

    // Автозаполнение названия (без расширения)
    titleInput.value = file.name.replace(/\.[^/.]+$/, "");
    titleInput.focus();

    showStatus('', '');
}

// --- Кнопка "Удалить / Сбросить" ---
removeFileBtn.addEventListener('click', () => {
    selectedFile = null;
    fileInput.value = ''; // Сброс input
    detailsStep.style.display = 'none';
    dropZone.style.display = 'block';
    progressContainer.style.display = 'none';
    showStatus('', '');
});

// --- Кнопка "Загрузить" ---
startUploadBtn.addEventListener('click', () => {
    if (!selectedFile) return;

    const title = titleInput.value.trim();
    if (!title) {
        showStatus('Пожалуйста, введите название видео', 'error');
        // Анимация тряски input, если пусто (опционально)
        titleInput.style.borderColor = '#ef4444';
        setTimeout(() => titleInput.style.borderColor = '#334155', 2000);
        return;
    }

    uploadVideo(selectedFile, title);
});

// --- Отправка на сервер ---
function uploadVideo(file, title) {
    // Блокируем интерфейс
    startUploadBtn.disabled = true;
    startUploadBtn.innerHTML = '<i class="fa-solid fa-spinner fa-spin"></i> Загрузка...';
    titleInput.disabled = true;

    progressContainer.style.display = 'block';
    progressFill.style.width = '0%';
    progressText.textContent = '0%';

    const formData = new FormData();
    formData.append('videoTitle', title);
    formData.append('videoFile', file);

    const xhr = new XMLHttpRequest();

    xhr.upload.addEventListener('progress', (event) => {
        if (event.lengthComputable) {
            const percentComplete = Math.round((event.loaded / event.total) * 100);
            progressFill.style.width = percentComplete + '%';
            progressText.textContent = percentComplete + '%';
        }
    });

    xhr.addEventListener('load', () => {
        if (xhr.status >= 200 && xhr.status < 300) {
            progressFill.style.width = '100%';
            progressText.textContent = '100%';
            showStatus('Видео успешно загружено!', 'success');

            // Сброс кнопки
            startUploadBtn.innerHTML = '<i class="fa-solid fa-check"></i> Готово';
        } else {
            showStatus('Ошибка сервера: ' + xhr.status, 'error');
            resetUIState();
        }
    });

    xhr.addEventListener('error', () => {
        showStatus('Ошибка сети', 'error');
        resetUIState();
    });

    xhr.open('POST', '/upload-video', true);
    xhr.send(formData);
}

function resetUIState() {
    startUploadBtn.disabled = false;
    startUploadBtn.innerHTML = '<i class="fa-solid fa-upload"></i> Загрузить на сервер';
    titleInput.disabled = false;
}

function showStatus(message, type) {
    statusText.textContent = message;
    statusText.className = 'status-message';
    if (type === 'success') statusText.classList.add('status-success');
    if (type === 'error') statusText.classList.add('status-error');
}