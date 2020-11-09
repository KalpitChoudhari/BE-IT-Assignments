package PackageDemo;

import java.text.ParseException;
import java.text.SimpleDateFormat;  

import java.util.Date; 

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;

import org.apache.hadoop.fs.Path;

import org.apache.hadoop.io.IntWritable;

import org.apache.hadoop.io.LongWritable;

import org.apache.hadoop.io.Text;

import org.apache.hadoop.mapreduce.Job;

import org.apache.hadoop.mapreduce.Mapper;

import org.apache.hadoop.mapreduce.Reducer;

import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;

import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import org.apache.hadoop.util.GenericOptionsParser;

public class WordCount {

public static void main(String [] args) throws Exception

{

Configuration c=new Configuration();

String[] files=new GenericOptionsParser(c,args).getRemainingArgs();

Path input=new Path(files[0]);

Path output=new Path(files[1]);

Job j=new Job(c,"wordcount");

j.setJarByClass(WordCount.class);

j.setMapperClass(MapForWordCount.class);

j.setReducerClass(ReduceForWordCount.class);

j.setOutputKeyClass(Text.class);

j.setOutputValueClass(IntWritable.class);

FileInputFormat.addInputPath(j, input);

FileOutputFormat.setOutputPath(j, output);

System.exit(j.waitForCompletion(true)?0:1);

}

public static class MapForWordCount extends Mapper<LongWritable, Text, Text, IntWritable>{

public void map(LongWritable key, Text value, Context con) throws IOException, InterruptedException

{

	String line = value.toString();
	String[] words=line.split(",");
	
	//Getting IP Address from File i.e. Location 1
	String IPAddr = words[1];				
	
	//Get the Start DATE from File
	String start_day[] = words[5].split(" ");
	//Taking out Year from Start Date
	String start_year = start_day[0];
	//Taking out time from Start Date
	String start_tm = start_day[1];
	
	//Get the End DATE form File
	String end_day[] = words[7].split(" ");
//	String end_year = end_day[0];
	//Taking out time form End Date
	String end_tm = end_day[1];
	
	Date date1 = null;
	Date date2 = null;
	SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss");
	
	try {
		date1= format.parse(start_tm);
	} catch (ParseException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	
	try {
		date2=format.parse(end_tm);
	} catch (ParseException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	
	//Calculating Total time difference between 2 dates
	long diff = date2.getTime() - date1.getTime();
	String IPYR = IPAddr +"\t"+ start_year; 
 	
	Text outputKey = new Text(IPYR);
	
	//Passing value as the total time difference instead of 1.
	IntWritable outputValue = new IntWritable((int)diff);

	con.write(outputKey, outputValue);

}

}

public static class ReduceForWordCount extends Reducer<Text, IntWritable, Text, IntWritable>

{

public void reduce(Text word, Iterable<IntWritable> values, Context con) throws IOException, InterruptedException

{

int sum = 0;

   for(IntWritable value : values)

   {

   sum += value.get();

   }

   con.write(word, new IntWritable(sum));

}

}

}