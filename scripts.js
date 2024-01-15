const products = [
    { id: 1, name: 'Chocolate', price: 75.99, available: 5 },
    { id: 2, name: 'Biscuit', price: 35.99, available: 3 },
    { id: 3, name: 'Chips', price: 99.99, available: 10 },
    { id: 4, name: 'Cookies', price: 49.99, available: 7 },
    { id: 5, name: 'Cold Drink', price: 25.99, available: 15 }
    // Add more products as needed
];

let cart = [];

function displayProductSelection() {
    const productList = document.getElementById('productList');

    // Populate dropdown with available product names
    products.forEach(product => {
        if (product.available > 0) {
            const option = document.createElement('option');
            option.value = product.id;
            option.textContent = `${product.name} - ₹${product.price.toFixed(2)}`;
            productList.appendChild(option);
        }
    });
}

function addToCart() {
    const selectedProductId = document.getElementById('productList').value;
    const selectedProduct = products.find(product => product.id === parseInt(selectedProductId));

    const quantity = parseInt(document.getElementById('quantity').value);

    if (selectedProduct && selectedProduct.available > 0 && quantity > 0) {
        const productTotal = selectedProduct.price * quantity;

        // Update availability count
        selectedProduct.available -= quantity;

        const productInCart = { ...selectedProduct, quantity, total: productTotal };
        cart.push(productInCart);
        updateCartTotal();
        displayProducts(); // Update the displayed availability
    } else {
        alert("Product not available or invalid quantity.");
    }
}

function updateCartTotal() {
    const cartTotalContainer = document.getElementById('cart-total');
    const cartContent = document.getElementById('cart-content');

    let total = 0;

    cartContent.innerHTML = '';

    cart.forEach(product => {
        total += product.total;

        const cartRow = document.createElement('tr');
        cartRow.innerHTML = `
            <td>${product.name}</td>
            <td>${product.quantity}</td>
            <td>₹${product.total.toFixed(2)}</td>
        `;
        cartContent.appendChild(cartRow);
    });

    cartTotalContainer.textContent = `Cart Total: ₹${total.toFixed(2)}`;
}

function checkout() {
    const userName = document.getElementById('userName').value.trim(); // Get user's name
    const cartTotal = cart.reduce((acc, product) => acc + product.total, 0);
    const selectedPaymentOption = document.querySelector('input[name="paymentOption"]:checked');

    if (userName === '') {
        alert("Please enter your name before checking out.");
        return;
    }

    if (selectedPaymentOption) {
        const paymentOption = selectedPaymentOption.value;
        alert(`Thank you, ${userName}!\nCheckout completed! Total amount: ₹${cartTotal.toFixed(2)}\nPayment Option: ${paymentOption}`);
        // Implement additional checkout logic as needed

        // Reset cart after checkout
        cart = [];
        updateCartTotal();
        displayProducts(); // Reset availability counts
    } else {
        alert("Please select a payment option.");
    }
}

function displayProducts() {
    const productsContent = document.getElementById('products-content');

    productsContent.innerHTML = '';

    products.forEach(product => {
        const productRow = document.createElement('tr');
        productRow.innerHTML = `
            <td>${product.name}</td>
            <td>₹${product.price.toFixed(2)}</td>
            <td>${product.available > 0 ? product.available : 'Not Available'}</td>
        `;
        productsContent.appendChild(productRow);
    });
}

function displayPaymentOptions() {
    const paymentOptionsContent = document.getElementById('payment-options-content');

    paymentOptionsContent.innerHTML = '';

    // Populate payment options radio buttons
    const paymentOptions = [
        { option: 'Cash', description: 'Pay with cash at the counter.' },
        { option: 'UPI', description: 'Transfer money using UPI.' },
        { option: 'Card', description: 'Pay with a credit or debit card.' }
    ];

    paymentOptions.forEach(option => {
        const optionInput = document.createElement('input');
        optionInput.type = 'radio';
        optionInput.name = 'paymentOption';
        optionInput.value = option.option;

        const optionLabel = document.createElement('label');
        optionLabel.textContent = `${option.option} - ${option.description}`;

        paymentOptionsContent.appendChild(optionInput);
        paymentOptionsContent.appendChild(optionLabel);
        paymentOptionsContent.appendChild(document.createElement('br'));
    });
}

// Call functions to display initial content
displayProductSelection();
displayProducts();
displayPaymentOptions();