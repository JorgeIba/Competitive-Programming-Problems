from pathlib import Path
# from string import ascii_lowercase


def decrypt(cipher, key):
    cipher_decrypted = []

    m = len(key)
    idx_key = 0
    for val in cipher:
        key_val = ord(key[idx_key])
        cipher_decrypted.append(chr(val ^ key_val))

        idx_key = (idx_key + 1) % m

    return "".join(cipher_decrypted)



p = Path(__file__).with_name("59.- XOR Decryption - cipher.txt")
with p.open('r') as f:
    cipher = list(map(int, f.read().split(',')))
    # print(cipher)


    a, b, c = 'e', 'x', 'p'
    cipher_decrypted = decrypt(cipher, a + b + c)
    print(cipher_decrypted)

    ans = sum(ord(char) for char in cipher_decrypted)
    print(ans)



    # for a in ascii_lowercase:
    #     for b in ascii_lowercase:
    #         for c in ascii_lowercase:

    #             cipher_decrypted = decrypt(cipher, a + b + c)
    #             whole_text = "".join(cipher_decrypted)
    #             if "the" in whole_text and "and" in whole_text:
    #                 print(whole_text, a, b, c)
    #                 print()






