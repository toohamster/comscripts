package cn.amlove.csvparse;

import java.io.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.logging.Logger;

import org.apache.commons.csv.*;

public class Main {

	static Logger log = Logger.getLogger("cn.amlove.csvparse");

	public static void main(String[] args) throws IOException {
		Data d1 = Main.getDataByResourcePath("/cn/amlove/csvparse/resources/test.csv");
		
		System.out.println("file: " + d1.getPath());
		System.out.println("headers: " + d1.getHeaders().keySet());
		System.out.println("values: " + d1.getRows());
		
		Data d2 = Main.getDataByPath("/C:/tmptt/TestDataDemo.csv");
		System.out.println("file: " + d2.getPath());
		System.out.println("headers: " + d2.getHeaders().keySet());
		System.out.println("values: " + d2.getRows());
		
		System.out.println("第1行数据: " + d2.getRows().get(0));
		System.out.println("第2行数据: " + d2.getRows().get(1));
		
		System.out.println("第1行数据 指定列获取: " + d2.getRows().get(0).get("$username"));
		System.out.println("第1行数据 指定列获取: " + d2.getRows().get(0).get("$password"));
		
	}

	public static Data getDataByPath(String path) {
		
		log.info("load file: " + path);
		
		Data data = new Data();		
		data.setPath(path);
		
		ArrayList<Map<String, String>> rows = new ArrayList<Map<String, String>>();
		
		try {
			Reader in = new FileReader(path);

			Iterable<CSVRecord> records = CSVFormat.EXCEL.withFirstRecordAsHeader().parse(in);
			
			Map<String, Integer> headers = ((CSVParser) records).getHeaderMap();
			data.setHeaders(headers);			
			log.info(headers.toString());
			for (CSVRecord record : records) {
				rows.add(record.toMap());
			}

		} catch (NullPointerException e) {
			log.severe("资源文件找不到: " + path);
		} catch (FileNotFoundException e) {
			log.severe("资源文件打不开: " + path);
		} catch (IOException e) {
			log.severe("资源文件打不开: " + path);
		}
		
		data.setRows(rows);

		return data;
	}
	
	public static Data getDataByResourcePath(String path) {
		log.info("load resource: " + path);
		try {
			path = Main.class.getResource(path).getPath();
			return getDataByPath(path);
		}
		catch (NullPointerException e) {
			log.severe("资源文件找不到: " + path);
		}
		
		return new Data();
	}

}
