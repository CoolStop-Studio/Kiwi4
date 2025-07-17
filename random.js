const Random = {
    rand_float() {
        return Math.random();
    },
    rand_int_range(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
    },
    rand_float_range(min, max) {
        return Math.random() * (max - min) + min;
    }
}