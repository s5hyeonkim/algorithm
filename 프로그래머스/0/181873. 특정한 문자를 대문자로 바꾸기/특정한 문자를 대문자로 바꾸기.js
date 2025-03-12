function solution(my_string, alp) {
    var answer;

    answer = my_string.split("").map((char, index, arr) => 
        char == alp ? char.toUpperCase() : char).join("");
    return answer;
}