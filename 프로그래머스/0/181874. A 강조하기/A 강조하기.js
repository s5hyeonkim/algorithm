function solution(myString) {
    var answer = '';
    answer = myString.split("").map((char, id) => {
        if (char == 'a')
            return 'A';
        else if (char >= 'B' && char <= 'Z')
            return char.toLowerCase();
        else
            return char;
    }).join("");
    return answer;
}