function solution(rny_string) {
    var answer;

    answer = rny_string.split("").reduce((acc, char, id, arr) => {
        if (char == "m")
        {
            acc.push("rn");
        }
        else
            acc.push(char);
        return acc;
    }, []).join("");

    return answer;
}