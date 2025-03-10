function solution(phone_number) {
    var answer;

    answer = Array.from(phone_number).map((num, id) => 
    {
        if (id < phone_number.length - 4) return '*';
        else return num;
    }).join('');
    return answer;
}