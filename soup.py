import urllib2
import re

url = urllib2.urlopen("http://hladnystudent.zones.sk/")
text = url.read()
soup = BeautifulSoup(text)
tables = soup.find_all('table')
 
def upper(): 
    hornasoup = BeautifulSoup(str(tables[1])) 
    list = []
    trs = hornasoup.find_all('tr')

    for i in range (1,trs.__len__()):        
         td = str(trs[i])
         tdsoup = BeautifulSoup(td)
         bordel = tdsoup.find_all('td')
         match = re.findall(r'<td>(.*?)<span',str(bordel[1]),re.DOTALL)
         bettermatch = re.findall(r'\n\s\s\s\s\s\s\s\s(.*?)\n',match[0])
         list.append(bettermatch[0])

    return list

def lower():
    dolnasoup = BeautifulSoup(str(tables[2])) 
    trs_dolna = dolnasoup.find_all('tr')
    list= []

    for i in range (1,trs_dolna.__len__()):        
        dtd = str(trs_dolna[i])
        dtdsoup = BeautifulSoup(dtd)
        dbordel = dtdsoup.find_all('td')

        dmatch = re.findall(r'<td>(.*?)<span',str(dbordel[1]),re.DOTALL)
        dbettermatch = re.findall(r'\n\s\s\s\s\s\s\s\s(.*?)\n',dmatch[0])
        list.append(dbettermatch[0])
    return list
       
    
    
