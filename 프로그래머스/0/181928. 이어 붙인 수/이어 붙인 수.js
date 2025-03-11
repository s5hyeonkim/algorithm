function solution(num_list) {
    var num, num2;

    num = 0; num2 = 0;
    num_list.map((id) => {
        if (id % 2)
            num = num * 10 + id;
        else
            num2 = num2 * 10 + id;
    });
    return num + num2;
}