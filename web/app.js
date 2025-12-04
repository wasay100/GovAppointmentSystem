const offices = {
    "Karachi": ["NADRA Saddar", "NADRA Clifton", "Passport Office Clifton"],
    "Lahore": ["NADRA Gulberg", "NADRA Model Town", "Passport Office Gulberg"],
    "Islamabad": ["NADRA G-6", "NADRA F-8", "Passport Office F-6"]
};

document.getElementById('city')?.addEventListener('change', function() {
    const city = this.value;
    const officeSelect = document.getElementById('office');
    officeSelect.innerHTML = '<option value="">Select Office</option>';
    if (city && offices[city]) {
        offices[city].forEach(office => {
            const option = document.createElement('option');
            option.value = office;
            option.textContent = office;
            officeSelect.appendChild(option);
        });
    }
});

document.getElementById('loginForm')?.addEventListener('submit', function(e) {
    e.preventDefault();
    const userType = document.getElementById('userType').value;
    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;
    const messageDiv = document.getElementById('loginMessage');
    const validCredentials = {
        'citizen': {username: 'citizen1', password: 'pass123'},
        'staff': {username: 'staff1', password: 'staff123'},
        'admin': {username: 'admin', password: 'admin123'}
    };
    if (validCredentials[userType] && validCredentials[userType].username === username && validCredentials[userType].password === password) {
        messageDiv.innerHTML = '<div class="success">Login successful! Welcome, ' + userType + '</div>';
        localStorage.setItem('userType', userType);
        localStorage.setItem('username', username);
        setTimeout(() => { window.location.href = 'book.html'; }, 1500);
    } else {
        messageDiv.innerHTML = '<div class="error">Invalid credentials. Please try again.</div>';
    }
});

document.getElementById('bookingForm')?.addEventListener('submit', function(e) {
    e.preventDefault();
    const formData = {
        city: document.getElementById('city').value,
        office: document.getElementById('office').value,
        service: document.getElementById('service').value,
        date: document.getElementById('date').value,
        time: document.getElementById('time').value,
        cnic: document.getElementById('cnic').value,
        name: document.getElementById('name').value,
        phone: document.getElementById('phone').value
    };
    const cityCode = formData.city.substring(0, 3).toUpperCase();
    const confirmationCode = 'APT-' + cityCode + '-' + Math.floor(Math.random() * 1000);
    let appointments = JSON.parse(localStorage.getItem('appointments') || '[]');
    const appointment = Object.assign({}, formData, {confirmationCode: confirmationCode, timestamp: new Date().toISOString()});
    appointments.push(appointment);
    localStorage.setItem('appointments', JSON.stringify(appointments));
    const resultDiv = document.getElementById('bookingResult');
    resultDiv.innerHTML = '<div class="success"><h3>Appointment Booked Successfully!</h3><p><strong>Confirmation Code:</strong> ' + confirmationCode + '</p><p><strong>Name:</strong> ' + formData.name + '</p><p><strong>City:</strong> ' + formData.city + '</p><p><strong>Office:</strong> ' + formData.office + '</p><p><strong>Date:</strong> ' + formData.date + '</p><p><strong>Time:</strong> ' + formData.time + '</p></div>';
    this.reset();
});

document.getElementById('searchCNICForm')?.addEventListener('submit', function(e) {
    e.preventDefault();
    const cnic = document.getElementById('searchCNIC').value;
    const appointments = JSON.parse(localStorage.getItem('appointments') || '[]');
    const results = appointments.filter(app => app.cnic === cnic);
    displayResults(results);
});

document.getElementById('searchConfirmationForm')?.addEventListener('submit', function(e) {
    e.preventDefault();
    const code = document.getElementById('searchConfirmation').value;
    const appointments = JSON.parse(localStorage.getItem('appointments') || '[]');
    const results = appointments.filter(app => app.confirmationCode === code);
    displayResults(results);
});

document.getElementById('viewAllBtn')?.addEventListener('click', function() {
    const appointments = JSON.parse(localStorage.getItem('appointments') || '[]');
    displayResults(appointments);
});

function displayResults(results) {
    const resultsDiv = document.getElementById('searchResults');
    if (results.length === 0) {
        resultsDiv.innerHTML = '<div class="error">No appointments found.</div>';
        return;
    }
    let html = '<h3>Search Results:</h3>';
    results.forEach(app => {
        html += '<div class="appointment-card"><h4>' + app.name + ' - ' + app.confirmationCode + '</h4><p><strong>CNIC:</strong> ' + app.cnic + '</p><p><strong>City:</strong> ' + app.city + '</p><p><strong>Office:</strong> ' + app.office + '</p><p><strong>Service:</strong> ' + app.service + '</p><p><strong>Date:</strong> ' + app.date + '</p><p><strong>Time:</strong> ' + app.time + '</p><p><strong>Phone:</strong> ' + app.phone + '</p></div>';
    });
    resultsDiv.innerHTML = html;
}

const dateInput = document.getElementById('date');
if (dateInput) {
    const today = new Date().toISOString().split('T')[0];
    dateInput.setAttribute('min', today);
}
