import fs from 'fs';

function GetSumOfCalVals(data) {
    const lines = ExtractNums(data)
    let total = 0;

    lines.forEach(line => {
        const digits = line.replace(/\D/g, '');
        if (digits.length > 0) {
            const first = digits[0];
            const last = digits[digits.length - 1];
            const sum = Number(first + last);
            total += sum;
        }
    });

    return total;
}

function ExtractNums(data) {
    const copy = {
        'one': 'o1e',
        'two': 't2o',
        'three': 't3e',
        'four': 'f4r',
        'five': 'f5e',
        'six': 's6x',
        'seven': 's7n',
        'eight': 'e8t',
        'nine': 'n9e'
    };

    Object.keys(copy).forEach( key => {
        data = data.map( line => {
            return line.replaceAll(key, copy[key]);
        });
    });

    return data
}


const data = fs.readFileSync('input.txt', 'utf-8').trim().split('\n')

const res = GetSumOfCalVals(data)

console.log(`result is: ${res}`);
