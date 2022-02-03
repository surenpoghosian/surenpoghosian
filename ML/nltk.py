from wordnet import wordnet

syn = wordnet.synsets("apple")

print(syn[0].definition())

print(syn[0].examples())