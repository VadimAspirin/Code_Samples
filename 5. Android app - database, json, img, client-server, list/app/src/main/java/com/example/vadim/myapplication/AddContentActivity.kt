package com.example.vadim.myapplication

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import kotlinx.coroutines.experimental.android.UI
import kotlinx.coroutines.experimental.launch
import java.net.SocketTimeoutException


class AddContentActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add_content)

        val etName: EditText = findViewById(R.id.editTextName) as EditText
        val etImage: EditText = findViewById(R.id.editImage) as EditText
        val etYear: EditText = findViewById(R.id.editTextYear) as EditText
        val etCountry: EditText = findViewById(R.id.editTextCountry) as EditText
        val etGenre: EditText = findViewById(R.id.editTextGenre) as EditText
        val etDescription: EditText = findViewById(R.id.editTextDescription) as EditText

        val btnAdd: Button = findViewById(R.id.buttonAddNewContentIn) as Button
        val oclBtnOk = object : View.OnClickListener {
            override fun onClick(v: View) {
                if(etName.getText().isEmpty() or
                   etImage.getText().isEmpty() or
                   etYear.getText().isEmpty() or
                   etCountry.getText().isEmpty() or
                   etGenre.getText().isEmpty() or
                   etDescription.getText().isEmpty()
                ) {
                    Toast.makeText(applicationContext, "Не все поля заполнены!", Toast.LENGTH_SHORT).show()
                } else {
                    val content = Content(etName.getText().toString(),
                                          etGenre.getText().toString(),
                                          etDescription.getText().toString(),
                                          etImage.getText().toString(),
                                          etCountry.getText().toString(),
                                          etYear.getText().toString())
                    launch(UI) {
                        try {
                            val addContentToServer = addContentToServer(content)
                            addContentToServer.start()
                            val serverContent = addContentToServer.await()
                            if(serverContent.toLowerCase().contains("\"__v\":0")){
                                Toast.makeText(applicationContext, "Данные успешно добавлены", Toast.LENGTH_SHORT).show()
                            } else {
                                Toast.makeText(applicationContext, "ОШИБКА: Сервер не может добавить данные", Toast.LENGTH_SHORT).show()
                            }
                        }
                        catch (e: SocketTimeoutException) {
                            Toast.makeText(applicationContext, "ОШИБКА: Нет соединения с сервером", Toast.LENGTH_SHORT).show()
                        }
                        finally {
                            closeActivity()
                        }
                    }
                }
                //etNum1.setText("Нажата кнопка ОК")
                //etNum2.setText(etNum1.getText().toString())
            }
        }

        btnAdd.setOnClickListener(oclBtnOk)

    }

    private fun closeActivity() {
        this.finish()
    }
}
