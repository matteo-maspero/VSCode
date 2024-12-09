PATH = "C:\\Users\\mat.maspero\\VSCode\\Assets\\"

class City:
	def __init__(self, istat, name, province, region, prefix, postalCode, fiscalCode, population, link):
		self.__istat = istat
		self.__name = name
		self.__province = province
		self.__region = region
		self.__prefix = prefix
		self.__postalCode = postalCode
		self.__fiscalCode = fiscalCode
		self.__population = population
		self.__link = link

def main():
	myCities = []
	
	with open(PATH + 'listacomuni.txt', 'r') as file:
		for line in file:
			istat, name, province, region, prefix, postalCode, fiscalCode, population, link = line.strip().split(';')
			city = City(istat, name, province, region, prefix, postalCode, fiscalCode, population, link)
			myCities.append(city)
	
	for city in myCities:
		print(city.__dict__)

main()